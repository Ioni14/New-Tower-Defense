#pragma once

#include "AbstractSystem.h"

class Game;

class AIKillCreepSystem : public AbstractSystem
{
public:
    explicit AIKillCreepSystem(Game& game);
    ~AIKillCreepSystem();

    void removeMarkedEntities();

    void update(const sf::Time& dt);

private:
    Game& mGame;
};
