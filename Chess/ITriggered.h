#pragma once
#include <SFML/Graphics.hpp>

class ITriggered
{
public:
	ITriggered();
	virtual bool isTriggered(const sf::Vector2i& mousePosition) const = 0;
	~ITriggered();
};

