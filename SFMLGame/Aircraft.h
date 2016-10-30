#pragma once
#include "Entity.h"
#include "ResourceHolder.h"
class Aircraft:public Entity {
public:
	enum Type {
		Eagle,
		Raptor
	};
	explicit Aircraft(Type type, const TextureHolder& textures);
	virtual unsigned int getCategory() const;
private:
	Type mType;
	sf::Sprite mSprite;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};