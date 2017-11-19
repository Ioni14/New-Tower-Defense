#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "TextureManager.h"
#include "ShaderManager.h"
#include "RenderSystem.h"
#include "AnimateSystem.h"
#include "MovementSystem.h"
#include "AIFollowPathSystem.h"
#include "AIKillCreepSystem.h"
#include "Entity.h"
#include "Map.h"

class Game
{
public:
	Game();
	~Game();

	void run();

    std::vector<Entity*>& getCreeps();

private:
	void init();
	void processEvents();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void update(const sf::Time& dt);
	void render();
	void clean();

private:
    TextureManager mTextureManager;
    ShaderManager mShaderManager;
    RenderSystem mRenderSystem;
    AnimateSystem mAnimateSystem;
    MovementSystem mMovementSystem;
    AIFollowPathSystem mAIFollowPathSystem;
    AIKillCreepSystem mAIKillCreepSystem;

    sf::View mCamera;

	bool mRunning;
	sf::RenderWindow mWindow;

    std::vector<std::unique_ptr<Entity>> mEntities;
    std::vector<Entity*> mCreeps;
    Map mMap;

	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingLeft;
	bool mIsMovingRight;
};
