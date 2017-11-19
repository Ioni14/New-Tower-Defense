#include "CaracComponent.h"

CaracComponent::CaracComponent(int health) :
    mMaxHealth(health),
    mHealth(health)
{
}

CaracComponent::~CaracComponent()
{
}

bool CaracComponent::isDead() const
{
    return mHealth <= 0;
}
