#include "AbstractSystem.h"


AbstractSystem::AbstractSystem()
{
}

AbstractSystem::~AbstractSystem()
{
}

void AbstractSystem::registerEntity(Entity * entity)
{
    mEntities.push_back(entity);
}
