#pragma once

#include "AbstractSystem.h"

class MovementSystem : public AbstractSystem
{
public:
    MovementSystem();
    ~MovementSystem();

    void update(const sf::Time& dt);
};
