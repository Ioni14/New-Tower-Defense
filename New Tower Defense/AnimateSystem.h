#pragma once

#include "AbstractSystem.h"

class AnimateSystem : public AbstractSystem
{
public:
    AnimateSystem();
    ~AnimateSystem();

    virtual void update(const sf::Time& dt);
};
