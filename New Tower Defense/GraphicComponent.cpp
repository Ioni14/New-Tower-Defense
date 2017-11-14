#include "GraphicComponent.h"


GraphicComponent::GraphicComponent(const sf::Texture& texture, int side) :
    mSide(side),
    mTexture(texture),
    mAnimations(),
    mActualAnimation(nullptr),
    mActualAnimationFrameIndex(0),
    mTimeAnimation(sf::Time::Zero)
{
    /*
     * Pixel perfect => mSide == mTexture.getSize().x == mTexture.getSize().y
     */

    // top left
    mVertices[0].color = sf::Color::White;
    mVertices[0].position = sf::Vector2f(0, 0);
    mVertices[0].texCoords = sf::Vector2f(0, 0);

    // bottom left
    mVertices[1].color = sf::Color::White;
    mVertices[1].position = sf::Vector2f(0, static_cast<float>(mSide));
    mVertices[1].texCoords = sf::Vector2f(0, static_cast<float>(mTexture.getSize().y));

    // bottom right
    mVertices[2].color = sf::Color::White;
    mVertices[2].position = sf::Vector2f(static_cast<float>(mSide), static_cast<float>(mSide));
    mVertices[2].texCoords = sf::Vector2f(static_cast<float>(mTexture.getSize().x), static_cast<float>(mTexture.getSize().y));

    // top right
    mVertices[3].color = sf::Color::White;
    mVertices[3].position = sf::Vector2f(static_cast<float>(mSide), 0);
    mVertices[3].texCoords = sf::Vector2f(static_cast<float>(mTexture.getSize().x), 0);
}

GraphicComponent::~GraphicComponent()
{
}

void GraphicComponent::selectAnimation(const std::string& animationName)
{
    auto& selectedAnimation = mAnimations.find(animationName);
    if (selectedAnimation == mAnimations.end()) {
        return;
    }

    mActualAnimation = &selectedAnimation->second;
}
