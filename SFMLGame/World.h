#pragma once
#include <iostream>
#include <array>
#include <SFML\System\NonCopyable.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include "ResourceHolder.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "Aircraft.h"
#include "CommandQueue.h"

class World : private sf::NonCopyable {
public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time dt);
	void draw();
	CommandQueue& getCommandQueue();

private:
	void loadTextures();
	void buildScene();
	void adaptPlayerPosition();
	void adaptPlayerVelocity();


	enum Layer {
		Background,
		Air,
		LayerCount
	};

	sf::RenderWindow& mWindow;
	sf::View mWorldView;
	TextureHolder	mTextures;
	SceneNode mSceneGraph;
	std::array <SceneNode*, LayerCount> mSceneLayers;
	CommandQueue mCommandQueue;
	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	Aircraft* mPlayerAircraft;
};