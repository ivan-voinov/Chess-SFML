#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"

class SquareBuilder
{
private:
	sf::Color m_Color = sf::Color::White;
	sf::Vector2i m_Coordinates = sf::Vector2i(0,0);
	sf::Vector2f m_Position = sf::Vector2f(0,0);
	Square::State m_State = Square::State::IS_FREE;
	float m_Size = 0.0;

public:
	SquareBuilder(const sf::Vector2i& coordinates, float size);
	SquareBuilder& color(const sf::Color& color);
	SquareBuilder& position(const sf::Vector2f& position);
	SquareBuilder& state(const Square::State& state);
	Square build();
	~SquareBuilder();
};

