#include "stdafx.h"
#include "PauseState.h"
#include "ResourceHolder.h"
#include "Utility.h"

PauseState::PauseState(StateStack & stack, Context context)
	:State(stack,context)
	, mBackgroundSprite()
	, mPausedText()
	, mInstructionsText()
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f viewSize = context.window->getView().getSize();
	mPausedText.setFont(font);
	mPausedText.setString("Game Paused");
	mPausedText.setCharacterSize(70);
	centerOrigin(mPausedText);
	mPausedText.setPosition(0.5f*viewSize.x, 0.4*viewSize.y);
	mInstructionsText.setFont(font);
	mInstructionsText.setString("(Press Backspace to return to Main Menu)");
	centerOrigin(mInstructionsText);
	mInstructionsText.setPosition(0.5f*viewSize.x, 0.6f*viewSize.y);
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());
	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mInstructionsText);
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event & event)
{
	if (event.type != sf::Event::KeyPressed) {
		return false;
	}
	
	if (event.key.code == sf::Keyboard::Escape) {
		requestStackPop();
	}

	if (event.key.code == sf::Keyboard::BackSpace) {
		requestStateClear();
		requestStackPush(States::Menu);
	}

	return false;
}

