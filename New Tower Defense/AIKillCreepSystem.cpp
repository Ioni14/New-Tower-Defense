#include "AIKillCreepSystem.h"

#include "CaracComponent.h"
#include "AttackComponent.h"
#include "Game.h"
#include <iostream>

AIKillCreepSystem::AIKillCreepSystem(Game& game) :
    mGame(game)
{
}

AIKillCreepSystem::~AIKillCreepSystem()
{
}

void AIKillCreepSystem::removeMarkedEntities()
{
    for (const auto& entity : mEntities) {
        auto& attackComp = static_cast<AttackComponent&>(entity->getComponent(Component::Type::ATTACK));

        if (attackComp.mTarget == nullptr) {
            continue;
        }
        if (attackComp.mTarget->needToRemove()) {
            attackComp.mTarget = nullptr;
        }
    }

    AbstractSystem::removeMarkedEntities();
}

void AIKillCreepSystem::update(const sf::Time & dt)
{
    auto& creeps = mGame.getCreeps();

    for (const auto& entity : mEntities) {
        /*
         * pour chaque entity (Tower) :
         * - si cooldown pas up : on passe
         * - si target existe (!= nullptr) et pas mort (CaracComp::mHealth > 0) et à portée (distance tower-creep < mRange) : on lui envoie un projectile
         * - sinon : on recherche le premier creep vivant (CaracComp::mHealth > 0) à portée : on lui envoie un projectile
         * - si y a eu attaque : on reset le cooldown
         */

        auto& attackComp = static_cast<AttackComponent&>(entity->getComponent(Component::Type::ATTACK));

        if (!attackComp.isCooldownUp()) {
            attackComp.stepCooldown(dt);
            continue;
        }

        // tower cans attack
        
        if (attackComp.hasTarget()) {
            auto& caracComp = static_cast<CaracComponent&>(attackComp.mTarget->getComponent(Component::Type::CARAC));
            
            if (caracComp.isDead()) {
                attackComp.mTarget = nullptr;
            }
            else {
                auto towerToCreep = attackComp.mTarget->getPosition() - entity->getPosition();
                auto distanceTowerToCreep = towerToCreep.x * towerToCreep.x + towerToCreep.y * towerToCreep.y;
                
                // distance is squared
                if (distanceTowerToCreep > attackComp.mRange * attackComp.mRange) {
                    // far away
                    attackComp.mTarget = nullptr;
                }
            }
        }

        if (!attackComp.hasTarget()) {
            // target lost or no target : find a new target (first found in range)

            for (auto& creep : creeps) {
                auto towerToCreep = creep->getPosition() - entity->getPosition();
                auto distanceTowerToCreep = towerToCreep.x * towerToCreep.x + towerToCreep.y * towerToCreep.y;
                // distance is squared
                if (distanceTowerToCreep > attackComp.mRange * attackComp.mRange) {
                    // far away
                    continue;
                }

                auto& caracComp = static_cast<CaracComponent&>(creep->getComponent(Component::Type::CARAC));
                if (caracComp.isDead()) {
                    continue;
                }

                // found good one
                attackComp.mTarget = creep;

                break;
            }
        }

        if (!attackComp.hasTarget()) {
            // no target available
            continue;
        }

        attackComp.resetCooldown(); // wait for the next attack

        // TODO : create a projectile Entity

        auto& caracComp = static_cast<CaracComponent&>(attackComp.mTarget->getComponent(Component::Type::CARAC));
        caracComp.mHealth -= attackComp.mRawDamage;

        if (caracComp.isDead()) {
            attackComp.mTarget = nullptr;
        }

        // create the attack entity with all damage bonus/malus
        // example : raw damage of 100 + BUFF physical damage of 50% = 100 * 1.5 = 150 + DEBUFF critical damage 10%
        // critical attribute base : 30% - debuff = 30% - 10% = 20%
        // => attack entity get 150 damage and 20% crit
        // 20% chances for 150 * 2 = 300 damages (crit)
        // 80% chances for 150 * 1 = 150 damages (normal)
        // resolution : per target compute buff and debuff and attributes
        // example : target with BUFF reduction damage of 25% + attribute armor of 70% + attribute defense of 10%
        // => 150 damages * 0.75 * 0.30 = 33.75. 20% crit - 10% def = 10% crit. 
        // 10% chances for 33.75 * 2 = ceil(67.5) = 68
        // 90% chances for 33.75 * 1 = ceil(33.75) = 34

        // attributes : 
        // health (0 = dead) 
        // damage (physical, fire, frost, nature, shadow, light) in AttackComponent
        // critical (chances to do x2 damages) 
        // defense (reduce incoming critical) 
        // haste (up frequency of attacks)
    }
}
