#include "Entity.h"

unsigned int Entity::mNextId = 1;

Entity::Entity() :
    mId(0),
    mComponents(),
    mFlags(0),
    mNeedToRemove(false)
{
}

Entity::UPtr Entity::create()
{
    auto entity = std::make_unique<Entity>();
    entity->mId = mNextId++;

    return entity;
}

void Entity::setFlags(unsigned int flags)
{
    mFlags = flags;
}

bool Entity::hasFlag(unsigned int flag) const
{
    return (mFlags & flag) > 0;
}

void Entity::addComponent(Component::UPtr&& component)
{
    if (component == nullptr) {
        throw std::logic_error("Component must not be null.");
    }
    mComponents.insert({ component->getType(), std::move(component) });
}

Component& Entity::getComponent(Component::Type type)
{
    auto& it = mComponents.find(type);
    if (it == mComponents.end() || it->second == nullptr) {
        throw std::logic_error("Component does not exist.");
    }

    return *(it->second.get());
}

Component* Entity::getPtrComponent(Component::Type type)
{
    auto& it = mComponents.find(type);
    if (it == mComponents.end() || it->second == nullptr) {
        return nullptr;
    }

    return it->second.get();
}
