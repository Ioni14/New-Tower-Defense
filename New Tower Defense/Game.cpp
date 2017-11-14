#include "Game.h"
#include "VelocityComponent.h"
#include "GraphicComponent.h"
#include <iostream>
#include <memory>

Game::Game() :
    mTextureManager(),
    mRenderSystem(mWindow),
    mAnimateSystem(),
    mMovementSystem(),
    mCamera(),
	mRunning(false),
	mWindow(sf::VideoMode(600, 800), "Tower Defense", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize),
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

    mTextureManager.load(TextureManager::ID::PLAYER_SPRITESHEET, "./textures/spritesheet_40px.png");

    for (int i = 0; i < 1; i++) {
        auto&& entity = Entity::create();
        entity->setFlags(Entity::Flags::player);
        entity->setPosition(2 * 40, 2 * 40);
        {
            auto&& comp = std::make_unique<VelocityComponent>(50.f);
            comp->setVelocity(sf::Vector2f(1.f, 0.f));
            entity->addComponent(std::move(comp));
        }
        {
            auto&& comp = std::make_unique<GraphicComponent>(mTextureManager.get(TextureManager::ID::PLAYER_SPRITESHEET), 40);
            {
                auto durationFrame = sf::milliseconds(80);
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
                auto durationFrame = sf::milliseconds(60);
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
        mRenderSystem.registerEntity(entity.get());
        mAnimateSystem.registerEntity(entity.get());
        mMovementSystem.registerEntity(entity.get());

        mEntities.push_back(std::move(entity));
    }

    mCamera.setSize(static_cast<float>(mWindow.getSize().x), static_cast<float>(mWindow.getSize().y));
    mCamera.setCenter(static_cast<float>(mWindow.getSize().x / 2.f), static_cast<float>(mWindow.getSize().y / 2.f));
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

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			mRunning = false;
			break;
		case sf::Event::Resized:
            mCamera.setSize(event.size.width, event.size.height);
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

    mMovementSystem.update(dt);
    mAnimateSystem.update(dt);
}

void Game::render()
{
    mWindow.setView(sf::View(
        sf::Vector2f(static_cast<int>(mCamera.getCenter().x), static_cast<int>(mCamera.getCenter().y)),
        sf::Vector2f(static_cast<int>(mCamera.getSize().x), static_cast<int>(mCamera.getSize().y)))
    );

	mWindow.clear(sf::Color(3, 169, 244));
    mWindow.draw(mMap);
    mRenderSystem.update();
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
