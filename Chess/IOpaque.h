#pragma once
#include <SFML/Graphics.hpp>

class IOpaque
{
public:
	virtual void setOpacity(sf::Uint8 opacity) = 0;
};

