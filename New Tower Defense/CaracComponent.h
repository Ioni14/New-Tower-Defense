#pragma once

#include "Component.h"

class CaracComponent : public Component
{
public:
    CaracComponent(int health);
    ~CaracComponent();

    bool isDead() const;

    inline virtual Type getType() const {
        return Type::CARAC;
    }

public:
    int mMaxHealth;
    int mHealth;
};
