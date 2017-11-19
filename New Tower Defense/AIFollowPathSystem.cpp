#define _USE_MATH_DEFINES

#include "AIFollowPathSystem.h"
#include "WaypointComponent.h"
#include "VelocityComponent.h"
#include "GraphicComponent.h"
#include "Game.h"
#include <iostream>
#include <cmath>

AIFollowPathSystem::AIFollowPathSystem(const Map& map, Game& game) :
    mMap(map),
    mGame(game)
{
}

AIFollowPathSystem::~AIFollowPathSystem()
{
}

void AIFollowPathSystem::update(const sf::Time& dt)
{
    for (const auto& entity : mEntities) {
        auto& velocityComp = static_cast<VelocityComponent&>(entity->getComponent(Component::Type::VELOCITY));
        auto& waypointComp = static_cast<WaypointComponent&>(entity->getComponent(Component::Type::WAYPOINT));

        auto currentWaypoint = mMap.getWaypoint(waypointComp.mCurrentIndex);

        // get the distance between entity and current waypoint
        auto positionToCurrentWaypoint = currentWaypoint.location - entity->getPosition();
        auto squaredPositionToCurrentWaypointDistance = positionToCurrentWaypoint.x * positionToCurrentWaypoint.x + positionToCurrentWaypoint.y * positionToCurrentWaypoint.y;
        
        // get the distance that entity move this frame
        auto frameMove = velocityComp.getNormalizedVelocity() * velocityComp.mSpeed * dt.asSeconds();
        auto squaredMovingDistance = frameMove.x * frameMove.x + frameMove.y * frameMove.y;

        // if entity is close enough to the current waypoint
        if (squaredPositionToCurrentWaypointDistance < squaredMovingDistance) {
            if (currentWaypoint.end) {
                // entity is arrived
                velocityComp.setVelocity(sf::Vector2f(0, 0));
                mGame.handleArrivedEntity(*entity);

                continue;
            }
            // go to the next
            waypointComp.mPreviousIndex = waypointComp.mCurrentIndex;
            ++waypointComp.mCurrentIndex;

            currentWaypoint = mMap.getWaypoint(waypointComp.mCurrentIndex);

            positionToCurrentWaypoint = currentWaypoint.location - entity->getPosition();

            auto angleInRadians = std::atan2(positionToCurrentWaypoint.y, positionToCurrentWaypoint.x);

            auto& graphicComp = static_cast<GraphicComponent&>(entity->getComponent(Component::Type::GRAPHIC));
            if (angleInRadians >= 1.f * M_PI_4 && angleInRadians < 3.f * M_PI_4) {
                graphicComp.selectAnimation("DOWN");
            }
            else if (angleInRadians >= 3.f * M_PI_4 || angleInRadians < -3.f * M_PI_4) {
                graphicComp.selectAnimation("LEFT");
            }
            else if (angleInRadians >= -3.f * M_PI_4 && angleInRadians < -1.f * M_PI_4) {
                graphicComp.selectAnimation("UP");
            }
            else {
                graphicComp.selectAnimation("RIGHT");
            }

            velocityComp.setVelocity(positionToCurrentWaypoint);
        }
    }
}
