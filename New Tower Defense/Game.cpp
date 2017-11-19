#include "Game.h"
#include "VelocityComponent.h"
#include "GraphicComponent.h"
#include "WaypointComponent.h"
#include "CaracComponent.h"
#include "AttackComponent.h"
#include <iostream>
#include <memory>

Game::Game() :
    mTextureManager(),
    mShaderManager(),
    mRenderSystem(mWindow),
    mAnimateSystem(),
    mMovementSystem(),
    mAIFollowPathSystem(mMap, *this),
    mAIKillCreepSystem(*this),
    mCamera(),
	mRunning(false),
	mWindow(sf::VideoMode(1200, 800), "Tower Defense", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize),
    mEntities(0),
    mMap(mTextureManager),
	mIsMovingUp(false),
	mIsMovingDown(false),
	mIsMovingLeft(false),
	mIsMovingRight(false)
{
}

Game::~Game()
{
	mWindow.close();
}

void Game::init()
{
    mMap.create("./maps/map1.tmx");

    mTextureManager.load(TextureManager::ID::PLAYER_SPRITESHEET, "./textures/spritesheet_with_tower_40px.png");
    mShaderManager.loadMultiple(ShaderManager::ID::ENTITY, "./shaders/entity.vert", "./shaders/entity.frag");

    for (auto i = 0; i < 10; i++) {
        auto&& entity = Entity::create();
        entity->setFlags(Entity::Flags::creep);
        entity->setPosition(2 * 40 - (i * 50), 2 * 40);
        {
            auto&& comp = std::make_unique<VelocityComponent>(100.f + (std::rand() % 200));
            comp->setVelocity(sf::Vector2f(1.f, 0.f));
            entity->addComponent(std::move(comp));
        }
        {
            auto&& comp = std::make_unique<WaypointComponent>();
            entity->addComponent(std::move(comp));
        }
        {
            auto&& comp = std::make_unique<GraphicComponent>(mTextureManager.get(TextureManager::ID::PLAYER_SPRITESHEET));
            auto durationFrame = sf::milliseconds(30);
            {
                std::vector<AnimationFrame> animations(0);
                animations.push_back(AnimationFrame(sf::IntRect(40 * 0, 176, 40, 220 - 176), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 1, 176, 40, 220 - 176), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 2, 176, 40, 220 - 176), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 3, 176, 40, 220 - 176), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 4, 176, 40, 220 - 176), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 5, 176, 40, 220 - 176), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 6, 176, 40, 220 - 176), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 7, 176, 40, 220 - 176), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 8, 176, 40, 220 - 176), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 9, 176, 40, 220 - 176), durationFrame));
                comp->mAnimations.insert({ "DOWN", std::move(animations) });
            }
            {
                std::vector<AnimationFrame> animations(0);
                animations.push_back(AnimationFrame(sf::IntRect(40 * 0, 220, 40, 260 - 220), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 1, 220, 40, 260 - 220), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 2, 220, 40, 260 - 220), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 3, 220, 40, 260 - 220), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 4, 220, 40, 260 - 220), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 5, 220, 40, 260 - 220), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 6, 220, 40, 260 - 220), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 7, 220, 40, 260 - 220), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 8, 220, 40, 260 - 220), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 9, 220, 40, 260 - 220), durationFrame));
                comp->mAnimations.insert({ "LEFT", std::move(animations) });
            }
            {
                std::vector<AnimationFrame> animations(0);
                animations.push_back(AnimationFrame(sf::IntRect(40 * 0, 260, 40, 304 - 260), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 1, 260, 40, 304 - 260), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 2, 260, 40, 304 - 260), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 3, 260, 40, 304 - 260), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 4, 260, 40, 304 - 260), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 5, 260, 40, 304 - 260), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 6, 260, 40, 304 - 260), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 7, 260, 40, 304 - 260), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 8, 260, 40, 304 - 260), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 9, 260, 40, 304 - 260), durationFrame));
                comp->mAnimations.insert({ "UP", std::move(animations) });
            }
            {
                std::vector<AnimationFrame> animations(0);
                animations.push_back(AnimationFrame(sf::IntRect(40 * 0, 304, 40, 347 - 304), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 1, 304, 40, 347 - 304), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 2, 304, 40, 347 - 304), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 3, 304, 40, 347 - 304), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 4, 304, 40, 347 - 304), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 5, 304, 40, 347 - 304), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 6, 304, 40, 347 - 304), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 7, 304, 40, 347 - 304), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 8, 304, 40, 347 - 304), durationFrame));
                animations.push_back(AnimationFrame(sf::IntRect(40 * 9, 304, 40, 347 - 304), durationFrame));
                comp->mAnimations.insert({ "RIGHT", std::move(animations) });
            }
            comp->selectAnimation("RIGHT");
            entity->addComponent(std::move(comp));
        }
        {
            auto&& comp = std::make_unique<CaracComponent>(100);
            entity->addComponent(std::move(comp));
        }
        mRenderSystem.registerEntity(entity.get());
        mAnimateSystem.registerEntity(entity.get());
        mMovementSystem.registerEntity(entity.get());
        mAIFollowPathSystem.registerEntity(entity.get());

        mCreeps.push_back(entity.get());
        mEntities.push_back(std::move(entity));
    }

    // Towers
    for (auto i = 0; i < 16; i++) {
        auto&& entity = Entity::create();
        entity->setFlags(Entity::Flags::tower);
        entity->setPosition(6 * 40 + (i / 7 * 40), 7 * 40 - (53 - 40) + ((i % 7) * 40)); // stretch the bottom (not the top) to the tile
        {
            auto&& comp = std::make_unique<GraphicComponent>(mTextureManager.get(TextureManager::ID::PLAYER_SPRITESHEET), sf::IntRect(120, 0, 40, 53), sf::Vector2i(40, 53));
            entity->addComponent(std::move(comp));
        }
        {
            auto&& comp = std::make_unique<AttackComponent>();
            comp->mCooldownFull = sf::milliseconds(500);
            comp->mRange = 100;
            comp->mRawDamage = 2;
            entity->addComponent(std::move(comp));
        }
        mRenderSystem.registerEntity(entity.get());
        mAIKillCreepSystem.registerEntity(entity.get());

        mEntities.push_back(std::move(entity));
    }

    mCamera.setSize(static_cast<float>(mWindow.getSize().x), static_cast<float>(mWindow.getSize().y));
    mCamera.setCenter(static_cast<float>(mWindow.getSize().x / 2.f) + 1, static_cast<float>(mWindow.getSize().y / 2.f) + 1);
}

void Game::run()
{
	init();

	sf::Clock timestepClock;
	auto timeSinceLastUpdate = sf::Time::Zero;
	const auto TIME_PER_FRAME = sf::seconds(1.0f / 60.0f);

	mRunning = true;
	while (mRunning)
	{
		processEvents();

		// update fixed timestep
		timeSinceLastUpdate += timestepClock.restart();
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;

			processEvents();
			update(TIME_PER_FRAME);
		}

		render();
	}

	clean();
}

std::vector<Entity*>& Game::getCreeps()
{
    return mCreeps;
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			mRunning = false;
			break;
		case sf::Event::Resized:
            mCamera.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape) {
				mRunning = false;
				break;
			}
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Button::Left) {
				//std::cout << "[Mouse Left Click] : " << event.mouseButton.x << "; " << event.mouseButton.y << std::endl;
			}
			break;
		}
	}
}

void Game::update(const sf::Time& dt)
{
	sf::Vector2f direction(0.f, 0.f);
	if (mIsMovingUp) {
		direction.y -= 1.f;
	}
	if (mIsMovingDown) {
		direction.y += 1.f;
	}
	if (mIsMovingLeft) {
		direction.x -= 1.f;
	}
	if (mIsMovingRight) {
		direction.x += 1.f;
	}

	// normalize direction
	auto len = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (len != 0) {
		direction /= len;
	}
    mCamera.move(direction * 400.f * dt.asSeconds());

    {
        sf::Clock clockFollowPath;
        mAIFollowPathSystem.update(dt);
        if (clockFollowPath.getElapsedTime().asMilliseconds() > 0) {
            std::cout << "follow path update : " << clockFollowPath.getElapsedTime().asMilliseconds() << " ms" << std::endl;
        }
    }

    {
        sf::Clock clockKillCreep;
        clockKillCreep.restart();
        mAIKillCreepSystem.update(dt);
        if (clockKillCreep.getElapsedTime().asMilliseconds() > 0) {
            std::cout << "kill creep update : " << clockKillCreep.getElapsedTime().asMilliseconds() << " ms" << std::endl;
        }
    }

    mMovementSystem.update(dt);
    mAnimateSystem.update(dt);
}

void Game::render()
{
    {
        // need even coordinates for the view
        auto center = sf::Vector2i(mCamera.getCenter());
        auto size = sf::Vector2i(mCamera.getSize());

        mWindow.setView(sf::View(
            sf::Vector2f(static_cast<float>(center.x % 2 == 1 ? center.x + 1 : center.x), static_cast<float>(center.y % 2 == 1 ? center.y + 1 : center.y)),
            sf::Vector2f(static_cast<float>(size.x % 2 == 1 ? size.x + 1 : size.x), static_cast<float>(size.y % 2 == 1 ? size.y + 1 : size.y))
        ));
    }

	mWindow.clear(sf::Color(3, 169, 244));
    mWindow.draw(mMap);
    mRenderSystem.render(mShaderManager.get(ShaderManager::ID::ENTITY));
	mWindow.display();
}

void Game::clean()
{
	mWindow.close();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Z) {
		mIsMovingUp = isPressed;
	}
	else if (key == sf::Keyboard::S) {
		mIsMovingDown = isPressed;
	}
	else if (key == sf::Keyboard::Q) {
		mIsMovingLeft = isPressed;
	}
	else if (key == sf::Keyboard::D) {
		mIsMovingRight = isPressed;
	}
}
