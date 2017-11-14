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
    explicit GraphicComponent(const sf::Texture& texture, int side = 64);
    ~GraphicComponent();

    void selectAnimation(const std::string& animationName);

    inline Type getType() const {
        return Type::GRAPHIC;
    }

public:
    int mSide; /**< pixels of a sprite side */
    const sf::Texture& mTexture; /**< given by TextureManager */
    std::array<sf::Vertex, 4> mVertices;

    std::unordered_map<std::string, std::vector<AnimationFrame>> mAnimations;
    std::vector<AnimationFrame>* mActualAnimation;
    int mActualAnimationFrameIndex;
    sf::Time mTimeAnimation;
};
