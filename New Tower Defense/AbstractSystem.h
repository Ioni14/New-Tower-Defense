#pragma once

#include "Entity.h"
#include <vector>

class AbstractSystem
{
public:
    AbstractSystem();
    virtual ~AbstractSystem();

    void registerEntity(Entity* entity);
    virtual void removeMarkedEntities();

    virtual void update(const sf::Time& dt) = 0;

protected:
    std::vector<Entity*> mEntities;
};
