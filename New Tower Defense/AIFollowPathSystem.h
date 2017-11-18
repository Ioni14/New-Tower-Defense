#pragma once

#include "AbstractSystem.h"
#include "Map.h"

class Game;

class AIFollowPathSystem : public AbstractSystem
{
public:
    explicit AIFollowPathSystem(const Map& map, const Game& game);
    ~AIFollowPathSystem();

    void update(const sf::Time& dt);

private:
    const Map& mMap;
    const Game& mGame;
};
