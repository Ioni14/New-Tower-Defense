#include "AttackComponent.h"

AttackComponent::AttackComponent() :
    mCooldownFull(sf::milliseconds(0)),
    mCooldown(sf::milliseconds(0)),
    mRawDamage(0),
    mRange(0),
    mTarget(nullptr)
{
}

AttackComponent::~AttackComponent()
{
}

bool AttackComponent::isCooldownUp() const
{
    return mCooldown <= sf::Time::Zero;
}

void AttackComponent::stepCooldown(const sf::Time& dt)
{
    mCooldown -= dt;
    if (mCooldown < sf::Time::Zero) {
        mCooldown = sf::Time::Zero;
    }
}

bool AttackComponent::hasTarget() const
{
    return mTarget != nullptr;
}

void AttackComponent::resetCooldown()
{
    mCooldown = mCooldownFull;
}
