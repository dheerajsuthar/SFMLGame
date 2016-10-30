#pragma once
#include <memory>
#include <vector>
#include <SFML/System/Time.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "Category.h"
#include "Command.h"

class SceneNode:public sf::Drawable, public sf::Transformable, private sf::NonCopyable {
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	SceneNode();
	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);
	void update(sf::Time dt);
	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;
	void onCommand(const Command& command, sf::Time dt);
	virtual unsigned int getCategory() const;
private:
	virtual void updateCurrent(sf::Time dt);
	void updateChildren(sf::Time dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildren(sf::RenderTarget & target, sf::RenderStates states) const;
	std::vector<Ptr> mChildren;
	SceneNode* mParent;
};