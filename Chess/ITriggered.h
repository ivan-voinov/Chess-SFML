#pragma once
#include <SFML/Graphics.hpp>

class ITriggered
{
public:
	virtual bool isTriggered(const sf::Vector2i& mousePosition) const = 0;
};

