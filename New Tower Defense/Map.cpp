#include "Map.h"

#include <iostream>

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
    const auto tilesize = tileset.getTileSize();

    const auto& layer = mMap.getLayers()[0];
    //layer->getType() : objectlayer | tilelayer
    //layer->getName() == "background"; // tilelayer
    //layer->getName() == "waypoints"; // objectlayer
    if (mMap.getOrientation() != tmx::Orientation::Orthogonal || layer->getType() != tmx::Layer::Type::Tile) {
        std::cerr << "The first layer is not a valid orthogonal tile layer." << std::endl;

        return;
    }
    const auto& tileLayer = dynamic_cast<const tmx::TileLayer* const>(layer.get());
    const auto& tiles = tileLayer->getTiles();

    // TODO : render only visible tiles
    for (auto y = 0; y < mMap.getTileCount().y; ++y) {
        for (auto x = 0; x < mMap.getTileCount().x; ++x) {
            const auto tileId = y * mMap.getTileCount().x + x;
            if (tileId >= tiles.size()) {
                std::cerr << "The tile " << x << ";" << y << " is over bounds." << std::endl;

                continue;
            }

            const auto idIndex = tiles[tileId].ID - tileset.getFirstGID();
            const auto i = idIndex % tileset.getColumnCount();
            const auto j = idIndex / tileset.getColumnCount();

            const auto tileX = i * tilesize.x + i * tileset.getSpacing() + tileset.getMargin();
            const auto tileY = j * tilesize.y + j * tileset.getSpacing() + tileset.getMargin();

            // top left
            {
                sf::Vertex vertex(sf::Vector2f(x * tilesize.x, y * tilesize.y), sf::Vector2f(tileX, tileY));
                mVertices.append(vertex);
            }
            // bottom left
            {
                sf::Vertex vertex(sf::Vector2f(x * tilesize.x, y * tilesize.y + tilesize.y), sf::Vector2f(tileX, tileY + tilesize.y));
                mVertices.append(vertex);
            }
            // bottom right
            {
                sf::Vertex vertex(sf::Vector2f(x * tilesize.x + tilesize.x, y * tilesize.y + tilesize.y), sf::Vector2f(tileX + tilesize.x, tileY + tilesize.y));
                mVertices.append(vertex);
            }
            // top right
            {
                sf::Vertex vertex(sf::Vector2f(x * tilesize.x + tilesize.x, y * tilesize.y), sf::Vector2f(tileX + tilesize.x, tileY));
                mVertices.append(vertex);
            }
        }
    }
}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.texture = &mTextureManager.get(TextureManager::ID::TILESET);
    target.draw(mVertices, states);
}
