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

    const Waypoint& getWaypoint(std::vector<Waypoint>::size_type index) const;
    std::vector<Waypoint>::size_type countWaypoints() const;

private:
    void createBackground(const tmx::TileLayer* const tileLayer);
    void createWaypoints(const tmx::ObjectGroup* const objectLayer);

private:
    tmx::Map mMap;
    TextureManager& mTextureManager;
    sf::VertexArray mVertices;

    std::vector<Waypoint> mWaypoints;
};
