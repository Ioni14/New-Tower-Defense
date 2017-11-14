#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>

class VelocityComponent :
    public Component
{
public:
    VelocityComponent();
    VelocityComponent(float speed, bool movable = true);
    ~VelocityComponent();

    const sf::Vector2f& getNormalizedVelocity() const;

    inline Type getType() const {
        return Type::VELOCITY;
    }

    void setVelocity(const sf::Vector2f velocity);

public:
    float mSpeed;
    bool mMovable;

private:
    mutable sf::Vector2f mNormalizedVelocity; /**< cache the normalized velocity */
    mutable bool mVelocityDirty;
    sf::Vector2f mVelocity;
};
