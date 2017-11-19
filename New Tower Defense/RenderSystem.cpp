#include "RenderSystem.h"

#include <SFML/Graphics.hpp>
#include "GraphicComponent.h"
#include "CaracComponent.h"
#include "AttackComponent.h"
#include <iostream>

RenderSystem::RenderSystem(sf::RenderTarget& target) :
    mTarget(target)
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::update(const sf::Time& dt)
{
}

void RenderSystem::render(sf::Shader& shader)
{
    // 1 draw per (shader/texture couple)
    // sort entities by z-order (top + height)

    // TODO : sort entities per texture and shader when multiple !

    for (const auto& entity : mEntities) {

        const auto& viewSize = mTarget.getView().getSize();
        const auto& viewCenter = mTarget.getView().getCenter();

        if (entity->getPosition().x >= viewCenter.x + viewSize.x / 2.f
            || entity->getPosition().y >= viewCenter.y + viewSize.y / 2.f
            || entity->getPosition().x < viewCenter.x - viewSize.x / 2.f - 40 // -40 for average width of entity
            || entity->getPosition().y < viewCenter.y - viewSize.y / 2.f - 40) { // -40 for average height of entity
            // not visible entity
            continue;
        }

        auto& graphicComp = static_cast<GraphicComponent&>(entity->getComponent(Component::Type::GRAPHIC));
        auto caracComp = entity->getPtrComponent(Component::Type::CARAC);

        shader.setUniform("texture", sf::Shader::CurrentTexture);

        auto states = sf::RenderStates::Default;
        states.texture = &graphicComp.mTexture;
        states.shader = &shader;
        states.transform *= entity->getTransform();
        sf::VertexArray vertices(sf::PrimitiveType::Quads);
        for (const auto& entityVertex : graphicComp.mVertices) {
            vertices.append(entityVertex);
        }

        if (caracComp != nullptr) {
            auto& caracCompCast = static_cast<CaracComponent&>(*caracComp);
            auto ratioHealth = static_cast<float>(caracCompCast.mHealth) / caracCompCast.mMaxHealth;

            // health bar bg
            vertices.append(sf::Vertex(sf::Vector2f(0.f, -10.f), sf::Color::Black, sf::Vector2f(-1.f, -1.f)));
            vertices.append(sf::Vertex(sf::Vector2f(0.f, -5.f), sf::Color::Black, sf::Vector2f(-1.f, -1.f)));
            vertices.append(sf::Vertex(sf::Vector2f(40.f, -5.f), sf::Color::Black, sf::Vector2f(-1.f, -1.f)));
            vertices.append(sf::Vertex(sf::Vector2f(40.f, -10.f), sf::Color::Black, sf::Vector2f(-1.f, -1.f)));

            // health bar fill
            vertices.append(sf::Vertex(sf::Vector2f(1.f, -9.f), sf::Color(58, 190, 28), sf::Vector2f(-1.f, -1.f)));
            vertices.append(sf::Vertex(sf::Vector2f(1.f, -6.f), sf::Color(58, 190, 28), sf::Vector2f(-1.f, -1.f)));
            vertices.append(sf::Vertex(sf::Vector2f((39.f - 1.f) * ratioHealth + 1.f, -6.f), sf::Color(58, 190, 28), sf::Vector2f(-1.f, -1.f)));
            vertices.append(sf::Vertex(sf::Vector2f((39.f - 1.f) * ratioHealth + 1.f, -9.f), sf::Color(58, 190, 28), sf::Vector2f(-1.f, -1.f)));
        }

        // gizmos
        if (false && entity->hasFlag(Entity::Flags::tower)) {
            auto& attackComp = static_cast<AttackComponent&>(entity->getComponent(Component::Type::ATTACK));
            // draw circle range
            sf::CircleShape rangeGizmo(attackComp.mRange);
            rangeGizmo.setFillColor(sf::Color(255, 128, 128, 50));
            rangeGizmo.setOutlineThickness(1.f);
            rangeGizmo.setOutlineColor(sf::Color(100, 50, 50, 255));
            rangeGizmo.setPosition(entity->getPosition() - sf::Vector2f(attackComp.mRange, attackComp.mRange));
            mTarget.draw(rangeGizmo);
        }

        mTarget.draw(vertices, states);
    }
}
