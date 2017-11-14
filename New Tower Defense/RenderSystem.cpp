#include "RenderSystem.h"

#include <SFML/Graphics.hpp>
#include "GraphicComponent.h"
#include <iostream>

RenderSystem::RenderSystem(sf::RenderTarget& target) :
    mTarget(target)
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::update(const sf::Time & dt)
{
    render();
}

void RenderSystem::render()
{
    // 1 draw per (shader/texture couple)
    // sort vertexarray by z-order (top + height)

    // TODO : sort entities per texture and shader !

    int cc = 0;
    for (const auto& entity : mEntities) {
        auto& graphicComp = dynamic_cast<GraphicComponent&>(entity->getComponent(Component::Type::GRAPHIC));

        auto states = sf::RenderStates::Default;
        states.texture = &graphicComp.mTexture;
        states.transform *= entity->getTransform();
        //states.shader = 
        sf::VertexArray vertices;
        vertices.setPrimitiveType(sf::PrimitiveType::Quads);
        for (auto& entityVertex : graphicComp.mVertices) {
            vertices.append(entityVertex);
        }

        mTarget.draw(vertices, states);
        cc++;
    }
}
