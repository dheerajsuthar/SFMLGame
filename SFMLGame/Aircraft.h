#pragma once
#include "Entity.h"
#include "ResourceHolder.h"
#include "Projectile.h"
#include "TextNode.h"

#include <SFML/Graphics/Sprite.hpp>

class Aircraft:public Entity {
public:
	enum Type {
		Eagle,
		Raptor,
		Avenger,
		TypeCount
	};
	Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts);
	virtual unsigned int getCategory() const;
	virtual sf::FloatRect getBoundingRect() const;
	virtual bool isMarkedForRemoval() const;
	bool isAllied() const;
	float getMaxSpeed() const;

	void increaseFireRate();
	void increaseSpread();
	void collectMissiles(unsigned int count);

	void fire();
	void launchMissiles();

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
	void updateMovementPattern(sf::Time dt);
	void checkPickupDrop(CommandQueue& commands);
	void checkProjectileLaunch(sf::Time dt, CommandQueue& commands);
	void createBullets(SceneNode& node, const TextureHolder& textures) const;
	void createProjectile(SceneNode& node, Projectile::Type type,
		float xOffset, float yOffset, const TextureHolder& textures) const;
	void createPickup(SceneNode& node, const TextureHolder& textures) const;
	void updateTexts();

	
	Type mType;
	sf::Sprite mSprite;
	Command mFireCommand;
	Command mMissileCommand;
	sf::Time mFireCountdown;
	bool mIsFiring;
	bool mIsLaunchingMissile;
	bool mIsMarkedForRemoval;
	int mFireRateLevel;
	int mSpreadLevel;
	int mMissileAmmo;
	Command mDropPickupCommand;
	float mTravelledDistance;
	std::size_t mDirectionIndex;
	TextNode* mHealthDisplay;
	TextNode* mMissileDisplay;
};