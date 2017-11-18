#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <string>
#include <unordered_map>

struct AnimationFrame {
    inline AnimationFrame() {}
    inline AnimationFrame(const sf::IntRect& rect, const sf::Time& duration) :
        rect(rect),
        duration(duration)
    {
    }

    sf::IntRect rect; /**< subtexture zone */
    sf::Time duration;
};

class GraphicComponent :
    public Component
{
public:
    GraphicComponent(
        const sf::Texture& texture, 
        const sf::IntRect& defaultTextureRect = sf::IntRect(0, 0, 0, 0), 
        const sf::Vector2i& defaultSize = sf::Vector2i(0, 0)
    );
    ~GraphicComponent();

    void selectAnimation(const std::string& animationName);
    void setDefaultTextureRect(const sf::IntRect& rect);
    void setDefaultSizeSprite(const sf::Vector2i& size);

    inline Type getType() const {
        return Type::GRAPHIC;
    }

public:
    const sf::Texture& mTexture; /**< given by TextureManager */
    std::array<sf::Vertex, 4> mVertices;

    std::unordered_map<std::string, std::vector<AnimationFrame>> mAnimations;
    std::vector<AnimationFrame>* mActualAnimation;
    int mActualAnimationFrameIndex;
    sf::Time mTimeAnimation;
};
