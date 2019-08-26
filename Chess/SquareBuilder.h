#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"

class SquareBuilder
{
private:
	sf::Color m_Color = sf::Color::White;
	sf::Vector2i m_Coordinates;
	sf::Vector2f m_Position = sf::Vector2f(0,0);
	double m_Size;
	bool m_Free = true;

public:
	SquareBuilder(const sf::Vector2i& coordinates, double size);
	SquareBuilder& color(const sf::Color& color);
	SquareBuilder& position(const sf::Vector2f& position);
	SquareBuilder& free(bool free);
	Square build();
	~SquareBuilder();
};

