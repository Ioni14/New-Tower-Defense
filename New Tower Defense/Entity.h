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
        tower = 0x04,
    };

    Entity();

    static UPtr create();

    void setFlags(unsigned int flags);
    bool hasFlag(unsigned int flag) const;

    void addComponent(Component::UPtr&& component);
    Component& getComponent(Component::Type type);
    Component* getPtrComponent(Component::Type type);

    inline void markRemove() {
        mNeedToRemove = true;
    }
    inline bool needToRemove() const {
        return mNeedToRemove;
    }

private:
    static unsigned int mNextId;

    unsigned int mId;

    std::unordered_map<Component::Type, std::unique_ptr<Component>> mComponents;
    unsigned int mFlags;

    bool mNeedToRemove;
};
