#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"
#include "Piece.h"

class SquareBuilder
{
private:
	sf::Color m_Color = sf::Color::White;
	sf::Vector2i m_Coordinates;
	sf::Vector2f m_Position = sf::Vector2f(0,0);
	std::unique_ptr<Piece> m_Piece = nullptr;
	double m_Size;
	bool m_Free = true;
	int m_TimesAttacked = 0;

public:
	SquareBuilder(const sf::Vector2i& coordinates, double size);
	SquareBuilder& color(const sf::Color& color);
	SquareBuilder& position(const sf::Vector2f& position);
	SquareBuilder& free(bool free);
	SquareBuilder& timesAttacked(int timesAttacked);
	SquareBuilder& piece(std::unique_ptr<Piece> piece);
	Square build();
	~SquareBuilder();
};

