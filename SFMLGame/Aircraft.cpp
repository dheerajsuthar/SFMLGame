#include "stdafx.h"
#include "Aircraft.h"

Textures::ID toTextureID(Aircraft::Type type) {
	switch (type) {
	case Aircraft::Type::Eagle:
		return Textures::Eagle;
	case Aircraft::Type::Raptor:
		return Textures::Raptor;
	}
	return Textures::Eagle;
}

Aircraft::Aircraft(Type type, const TextureHolder & textures):
	mType(type),mSprite(textures.get(toTextureID(type)))
{
	sf::FloatRect localBounds = mSprite.getLocalBounds();
	mSprite.setOrigin(localBounds.width / 2.f, localBounds.height / 2.f);
}

unsigned int Aircraft::getCategory() const
{
	switch (mType)
	{
	case Aircraft::Eagle:
		return Category::PlayerAircraft;
	default:
		return Category::EnemyAircraft;
	}
}

void Aircraft::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
