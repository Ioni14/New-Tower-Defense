#include "VelocityComponent.h"

VelocityComponent::VelocityComponent() :
    VelocityComponent(0.f, true)
{
}

VelocityComponent::VelocityComponent(float speed, bool movable) :
    mNormalizedVelocity(0.f, 0.f),
    mVelocityDirty(true),
    mVelocity(0.f, 0.f),
    mSpeed(speed),
    mMovable(movable)
{
}

VelocityComponent::~VelocityComponent()
{
}

const sf::Vector2f& VelocityComponent::getNormalizedVelocity() const
{
    if (!mVelocityDirty) {
        return mNormalizedVelocity;
    }

    mNormalizedVelocity = mVelocity;

    auto len = std::sqrt(mNormalizedVelocity.x * mNormalizedVelocity.x + mNormalizedVelocity.y * mNormalizedVelocity.y);
    if (len != 0) {
        mNormalizedVelocity /= len;
    }
    mVelocityDirty = false;

    return mNormalizedVelocity;
}

void VelocityComponent::setVelocity(const sf::Vector2f velocity)
{
    mVelocityDirty = true;
    mVelocity = velocity;
}
