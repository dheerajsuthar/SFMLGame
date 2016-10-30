#pragma once
#include <vector>
#include <map>
#include <functional>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include "State.h"

namespace sf {
	class Event;
	class RenderWindow;
}

class StateStack : private sf::NonCopyable {
public:
	enum Action
	{
		Push,
		Pop,
		Clear
	};

	explicit StateStack(State::Context context);
	template <typename T>
	void registerState(States::ID stateID);
	void update(sf::Time dt);
	void draw();
	void handleEvent(const sf::Event& event);
	void pushState(States::ID stateID);
	void popState();
	void clearState();
	bool isEmpty() const;

private:
	State::Ptr createState(States::ID stateID);
	void applyPendingChanges();
	struct PendingChange {
		explicit PendingChange(Action action, States::ID stateID = States::None);
		Action action;
		States::ID stateID;
	};
	
	std::vector<State::Ptr> mStack;
	std::vector<PendingChange> mPendingList;
	State::Context mContext;
	std::map<States::ID, std::function<State::Ptr()>> mFactories;
};

template <typename T>
void StateStack::registerState(States::ID stateID) {
	mFactories[stateID] = [this]()
	{
		return State::Ptr(new T(*this, mContext));
	};
}

