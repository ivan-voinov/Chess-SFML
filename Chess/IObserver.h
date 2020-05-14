#pragma once
#include <SFML/Window.hpp>

class IObserver
{
public:
	virtual void update(const sf::Event& event, const sf::Vector2i& mousePosition) = 0;
};

