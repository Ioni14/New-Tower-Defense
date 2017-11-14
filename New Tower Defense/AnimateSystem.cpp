#include "AnimateSystem.h"

#include "GraphicComponent.h"

AnimateSystem::AnimateSystem()
{
}

AnimateSystem::~AnimateSystem()
{
}

void AnimateSystem::update(const sf::Time& dt)
{
    for (const auto& entity : mEntities) {
        auto& graphicComp = dynamic_cast<GraphicComponent&>(entity->getComponent(Component::Type::GRAPHIC));

        graphicComp.mTimeAnimation += dt;

        // si on a dépassé le temps de la frame actuelle : on passe à la frame suivante
        const auto& frameDuration = graphicComp.mActualAnimation->at(graphicComp.mActualAnimationFrameIndex).duration;
        if (graphicComp.mTimeAnimation >= frameDuration) {
            graphicComp.mTimeAnimation -= frameDuration;
            graphicComp.mActualAnimationFrameIndex = (graphicComp.mActualAnimationFrameIndex + 1) % graphicComp.mActualAnimation->size();

            const auto& frameRect = graphicComp.mActualAnimation->at(graphicComp.mActualAnimationFrameIndex).rect;

            // mise à jour des vertices du sprite
            graphicComp.mVertices[0].position.x = 0;
            graphicComp.mVertices[0].position.y = 0;
            graphicComp.mVertices[0].texCoords.x = frameRect.left;
            graphicComp.mVertices[0].texCoords.y = frameRect.top;

            graphicComp.mVertices[1].position.x = 0;
            graphicComp.mVertices[1].position.y = frameRect.height;
            graphicComp.mVertices[1].texCoords.x = frameRect.left;
            graphicComp.mVertices[1].texCoords.y = frameRect.top + frameRect.height;

            graphicComp.mVertices[2].position.x = frameRect.width;
            graphicComp.mVertices[2].position.y = frameRect.height;
            graphicComp.mVertices[2].texCoords.x = frameRect.left + frameRect.width;
            graphicComp.mVertices[2].texCoords.y = frameRect.top + frameRect.height;

            graphicComp.mVertices[3].position.x = frameRect.width;
            graphicComp.mVertices[3].position.y = 0;
            graphicComp.mVertices[3].texCoords.x = frameRect.left + frameRect.width;
            graphicComp.mVertices[3].texCoords.y = frameRect.top;
        }
    }
}
