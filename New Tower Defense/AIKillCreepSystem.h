#pragma once

#include "AbstractSystem.h"

class Game;

class AIKillCreepSystem : public AbstractSystem
{
public:
    explicit AIKillCreepSystem(Game& game);
    ~AIKillCreepSystem();

    void update(const sf::Time& dt);

private:
    Game& mGame;
};
