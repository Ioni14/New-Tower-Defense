#pragma once

#include "Entity.h"
#include "AbstractSystem.h"
#include <vector>

class RenderSystem : public AbstractSystem
{
public:
    explicit RenderSystem(sf::RenderTarget& target);
    ~RenderSystem();

    virtual void update(const sf::Time& dt = sf::Time::Zero);
    void render(sf::Shader& shader);

private:

    sf::RenderTarget& mTarget;
};
