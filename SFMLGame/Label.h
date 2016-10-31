#pragma once
#include <SFML/Graphics/Text.hpp>
#include "Component.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

namespace GUI {
	class Label : public Component {
	public:
		typedef std::shared_ptr<Label> Ptr;

		Label(const std::string& text, const FontHolder& fonts);
		virtual bool isSelectable() const;
		void setText(const std::string& text);
		virtual void handleEvent(const sf::Event& event);

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		sf::Text mText;

	};
}
