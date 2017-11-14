#pragma once

#include <memory>

class Component
{
public:
    using UPtr = std::unique_ptr<Component>;
    enum class Type { VELOCITY, GRAPHIC /*SPRITE, PATH, ATTACK_TOWER, CARAC */ };

    Component();
    virtual ~Component();

    inline virtual Type getType() const = 0;
};
