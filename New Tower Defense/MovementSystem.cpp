
#include "MovementSystem.h"
#include "VelocityComponent.h"

MovementSystem::MovementSystem()
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::update(const sf::Time& dt)
{
    for (const auto& entity : mEntities) {
        auto& velocityComp = dynamic_cast<VelocityComponent&>(entity->getComponent(Component::Type::VELOCITY));

        if (velocityComp.mMovable) {
            entity->move(velocityComp.getNormalizedVelocity() * velocityComp.mSpeed * dt.asSeconds());
        }
    }
}
