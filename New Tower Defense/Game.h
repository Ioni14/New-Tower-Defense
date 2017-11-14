#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "TextureManager.h"
#include "RenderSystem.h"
#include "AnimateSystem.h"
#include "MovementSystem.h"
#include "Entity.h"
#include "Map.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	void init();
	void processEvents();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void update(const sf::Time& dt);
	void render();
	void clean();

private:
    TextureManager mTextureManager;
    RenderSystem mRenderSystem;
    AnimateSystem mAnimateSystem;
    MovementSystem mMovementSystem;
    sf::View mCamera;

	bool mRunning;
	sf::RenderWindow mWindow;

    std::vector<std::unique_ptr<Entity>> mEntities;
    Map mMap;

	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingLeft;
	bool mIsMovingRight;
};
