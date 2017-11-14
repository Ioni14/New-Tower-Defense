#pragma once

#include <string>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

struct Waypoint
{
    sf::Vector2f location;
    bool begin;
    bool end;
};

class Map : public sf::Drawable
{
public:
    explicit Map(TextureManager& textureManager);
    ~Map();

    void create(const std::string& filename);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    tmx::Map mMap;
    TextureManager& mTextureManager;
    sf::VertexArray mVertices;

    std::vector<Waypoint> mWaypoints;
};
