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

void AbstractSystem::removeMarkedEntities()
{
    mEntities.erase(
        std::remove_if(
            mEntities.begin(),
            mEntities.end(),
            [](Entity* entity) { return entity->needToRemove(); }
        ),
        mEntities.end()
    );
}
