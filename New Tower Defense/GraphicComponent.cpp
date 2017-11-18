#include "GraphicComponent.h"


GraphicComponent::GraphicComponent(const sf::Texture& texture, const sf::IntRect& defaultTextureRect, const sf::Vector2i& defaultSize) :
    mTexture(texture),
    mAnimations(),
    mActualAnimation(nullptr),
    mActualAnimationFrameIndex(0),
    mTimeAnimation(sf::Time::Zero)
{
    // top left
    mVertices[0].color = sf::Color::White;
    mVertices[0].position = sf::Vector2f(0, 0);
    mVertices[0].texCoords = sf::Vector2f(static_cast<float>(defaultTextureRect.left), static_cast<float>(defaultTextureRect.top));

    // bottom left
    mVertices[1].color = sf::Color::White;
    mVertices[1].position = sf::Vector2f(0, static_cast<float>(defaultSize.y));
    mVertices[1].texCoords = sf::Vector2f(static_cast<float>(defaultTextureRect.left), static_cast<float>(defaultTextureRect.top + defaultTextureRect.height));

    // bottom right
    mVertices[2].color = sf::Color::White;
    mVertices[2].position = sf::Vector2f(static_cast<float>(defaultSize.x), static_cast<float>(defaultSize.y));
    mVertices[2].texCoords = sf::Vector2f(static_cast<float>(defaultTextureRect.left + defaultTextureRect.width), static_cast<float>(defaultTextureRect.top + defaultTextureRect.height));

    // top right
    mVertices[3].color = sf::Color::White;
    mVertices[3].position = sf::Vector2f(static_cast<float>(defaultSize.x), 0);
    mVertices[3].texCoords = sf::Vector2f(static_cast<float>(defaultTextureRect.left + defaultTextureRect.width), static_cast<float>(defaultTextureRect.top));
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

void GraphicComponent::setDefaultTextureRect(const sf::IntRect& rect)
{
    // top left
    mVertices[0].texCoords = sf::Vector2f(static_cast<float>(rect.left), static_cast<float>(rect.top));

    // bottom left
    mVertices[1].texCoords = sf::Vector2f(static_cast<float>(rect.left), static_cast<float>(rect.top + rect.height));

    // bottom right
    mVertices[2].texCoords = sf::Vector2f(static_cast<float>(rect.left + rect.width), static_cast<float>(rect.top + rect.height));

    // top right
    mVertices[3].texCoords = sf::Vector2f(static_cast<float>(rect.left + rect.width), static_cast<float>(rect.top));
}

void GraphicComponent::setDefaultSizeSprite(const sf::Vector2i & size)
{
    // bottom left
    mVertices[1].position = sf::Vector2f(0, static_cast<float>(size.y));

    // bottom right
    mVertices[2].position = sf::Vector2f(static_cast<float>(size.x), static_cast<float>(size.y));

    // top right
    mVertices[3].position = sf::Vector2f(static_cast<float>(size.x), 0);
}
