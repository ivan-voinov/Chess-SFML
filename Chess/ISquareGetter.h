#pragma once
#include <SFML/Graphics.hpp>

class Square;

class ISquareGetter
{
public:
	virtual Square* getSquare(const sf::Vector2i coords) const = 0;
	virtual Square* getTriggeredSquare(const sf::Vector2i& mousePosition) = 0;
};

