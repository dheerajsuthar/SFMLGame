#include "stdafx.h"
#include "Player.h"
#include "Aircraft.h"
#include "CommandQueue.h"
#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std::placeholders;

struct AircraftMover {
	AircraftMover(float vx, float vy)
		:velocity(vx, vy) {}
	void operator() (Aircraft& aircraft, sf::Time dt) const {
		aircraft.accelerate(velocity*aircraft.getMaxSpeed());
	}

	sf::Vector2f velocity;
};
Player::Player()
	: mCurrentMissionStatus(MissionRunning)
{
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;
	mKeyBinding[sf::Keyboard::Space] = Fire;
	mKeyBinding[sf::Keyboard::M] = LaunchMissile;

	initializeActions();

	for (auto& pair : mActionBinding) {
		pair.second.category = Category::PlayerAircraft;
	}
}

void Player::handleEvent(const sf::Event & event, CommandQueue & commands)
{
	if (event.type == sf::Event::KeyPressed) {
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealTimeAction(found->second)) {
			commands.push(mActionBinding[found->second]);
		}
	}
}

void Player::handleRealTimeInput(CommandQueue & commands)
{
	for(auto pair: mKeyBinding) {
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second)) {
			commands.push(mActionBinding[pair.second]);
		}
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end();) {
		if (itr->second == action) {
//investigate this.. increment was earlier done in loop
			mKeyBinding.erase(itr++);
		} else {
			++itr;
		}
	}

	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action)
{
	for(auto pair: mKeyBinding) {
		if (pair.second == action) {
			return pair.first;
		}

	}
		return sf::Keyboard::Unknown;
}

void Player::setMissionStatus(Player::MissionStatus status) {
	mCurrentMissionStatus = status;
}

Player::MissionStatus Player::getMissionStatus() const {
	return mCurrentMissionStatus;
}

void Player::initializeActions()
{
	mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-1, 0));
	mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+1, 0));
	mActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0, -1));
	mActionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0, +1));
	mActionBinding[Fire].action = derivedAction<Aircraft>(
		[](Aircraft& a, sf::Time) { a.fire(); });
	mActionBinding[LaunchMissile].action = derivedAction<Aircraft>(
		[](Aircraft& a, sf::Time) { a.launchMissiles();});
}

bool Player::isRealTimeAction(Action action)
{
	switch (action)
	{
	case MoveLeft:
	case MoveRight:
	case MoveUp:
	case MoveDown:
	case Fire: 
		return true;
	default:
		return false;
	}
}
