#pragma once

#include "Component.h"
#include "SFML/Graphics.hpp"

class Entity;

class AttackComponent : public Component
{
public:
    AttackComponent();
    ~AttackComponent();

    bool isCooldownUp() const;
    void stepCooldown(const sf::Time& dt);
    bool hasTarget() const;
    void resetCooldown();

    inline virtual Type getType() const {
        return Type::ATTACK;
    }

public:
    sf::Time mCooldownFull; /**< total cooldown */
    sf::Time mCooldown; /**< actual cooldown. less than 0s => attack available */
    unsigned int mRawDamage; /**< raw damage */
    //float mPercentCritical; /**< percent of chances for critical attacks */
    float mRange; /**< distance for targeting/attacking creeps */
    Entity* mTarget; /**< actuel entity target (targetable && attackable) */
};
