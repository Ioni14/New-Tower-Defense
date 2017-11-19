#include "Map.h"

#include <iostream>
#include <algorithm>

Map::Map(TextureManager& textureManager) :
    mTextureManager(textureManager),
    mVertices(sf::PrimitiveType::Quads),
    mWaypoints(0)
{
}

Map::~Map()
{
}

void Map::create(const std::string & filename)
{
    if (!mMap.load(filename)) {
        std::cerr << "La map n'a pu être chargée." << std::endl;

        return;
    }
    const auto& tileset = mMap.getTilesets()[0];
    mTextureManager.load(TextureManager::ID::TILESET, tileset.getImagePath());

    for (auto& layer : mMap.getLayers()) {
        switch (layer->getType()) {
        case tmx::Layer::Type::Tile:
            createBackground(static_cast<const tmx::TileLayer* const>(layer.get()));
            break;
        case tmx::Layer::Type::Object:
            createWaypoints(static_cast<const tmx::ObjectGroup* const>(layer.get()));
            break;
        }
    }

    
}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.texture = &mTextureManager.get(TextureManager::ID::TILESET);
    target.draw(mVertices, states);
}

const Waypoint& Map::getWaypoint(std::vector<Waypoint>::size_type index) const
{
    if (index >= mWaypoints.size() || index < 0) {
        throw std::logic_error("This waypoint does not exist.");
    }

    return mWaypoints[index];
}

std::vector<Waypoint>::size_type Map::countWaypoints() const
{
    return mWaypoints.size();
}

void Map::createBackground(const tmx::TileLayer* const tileLayer)
{
    if (mMap.getOrientation() != tmx::Orientation::Orthogonal) {
        std::cerr << "The tile layer is not a valid orthogonal layer." << std::endl;

        return;
    }
    const auto& tileset = mMap.getTilesets()[0];
    const auto& tilesize = tileset.getTileSize();
    const auto& tiles = tileLayer->getTiles();

    // TODO : render only visible tiles
    for (unsigned int y = 0; y < mMap.getTileCount().y; ++y) {
        for (unsigned int x = 0; x < mMap.getTileCount().x; ++x) {
            const auto tileId = y * mMap.getTileCount().x + x;
            if (tileId >= tiles.size()) {
                std::cerr << "The tile " << x << ";" << y << " is over bounds." << std::endl;

                continue;
            }

            const auto idIndex = tiles[tileId].ID - tileset.getFirstGID();
            const auto i = idIndex % tileset.getColumnCount();
            const auto j = idIndex / tileset.getColumnCount();

            const auto tileX = static_cast<float>(i * tilesize.x + i * tileset.getSpacing() + tileset.getMargin());
            const auto tileY = static_cast<float>(j * tilesize.y + j * tileset.getSpacing() + tileset.getMargin());

            const auto tilePosition = sf::Vector2f(static_cast<float>(x * tilesize.x), static_cast<float>(y * tilesize.y));

            // top left
            {
                sf::Vertex vertex(tilePosition, sf::Vector2f(tileX, tileY));
                mVertices.append(vertex);
            }
            // bottom left
            {
                sf::Vertex vertex(sf::Vector2f(tilePosition.x, tilePosition.y + tilesize.y), sf::Vector2f(tileX, tileY + tilesize.y));
                mVertices.append(vertex);
            }
            // bottom right
            {
                sf::Vertex vertex(sf::Vector2f(tilePosition.x + tilesize.x, tilePosition.y + tilesize.y), sf::Vector2f(tileX + tilesize.x, tileY + tilesize.y));
                mVertices.append(vertex);
            }
            // top right
            {
                sf::Vertex vertex(sf::Vector2f(tilePosition.x + tilesize.x, tilePosition.y), sf::Vector2f(tileX + tilesize.x, tileY));
                mVertices.append(vertex);
            }
        }
    }
}

void Map::createWaypoints(const tmx::ObjectGroup* const objectLayer)
{
    auto objects = objectLayer->getObjects();
    
    // sort by order property of waypoint type
    std::sort(objects.begin(), objects.end(), [](const tmx::Object& o1, const tmx::Object& o2) -> bool {
        auto order1 = 0;
        auto order2 = 0;

        for (const auto& prop : o1.getProperties()) {
            if (prop.getName() == "order") {
                order1 = prop.getIntValue();
                break;
            }
        }
        for (const auto& prop : o2.getProperties()) {
            if (prop.getName() == "order") {
                order2 = prop.getIntValue();
                break;
            }
        }

        return order1 < order2;
    });

    for (const auto& object : objects) {
        auto begin = false;
        for (const auto& prop : object.getProperties()) {
            if (prop.getName() == "begin") {
                begin = prop.getBoolValue();
                break;
            }
        }
        auto end = false;
        for (const auto& prop : object.getProperties()) {
            if (prop.getName() == "end") {
                end = prop.getBoolValue();
                break;
            }
        }
        Waypoint waypoint = { sf::Vector2f(object.getPosition().x, object.getPosition().y), begin, end };
        mWaypoints.push_back(std::move(waypoint));
    }
}
