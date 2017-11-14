#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include "Component.h"

class Entity : private sf::NonCopyable, public sf::Transformable
{
public:
    using UPtr = std::unique_ptr<Entity>;

    enum Flags {
        player = 0x01,
        creep = 0x02,
    };

    Entity();

    static UPtr create();

    void setFlags(unsigned int flags);
    void addComponent(Component::UPtr&& component);
    Component& getComponent(Component::Type type);

private:
    static unsigned int mNextId;

    unsigned int mId;

    std::unordered_map<Component::Type, std::unique_ptr<Component>> mComponents;
    unsigned int mFlags;
};
