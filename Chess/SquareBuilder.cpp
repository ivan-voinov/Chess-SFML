#include "pch.h"
#include "SquareBuilder.h"


SquareBuilder::SquareBuilder(const sf::Vector2i& coordinates, double size)
{
	this->m_Coordinates = coordinates;
	this->m_Size = size;
}

SquareBuilder& SquareBuilder::color(const sf::Color& color)
{
	this->m_Color = color;
	return *this;
}

SquareBuilder& SquareBuilder::position(const sf::Vector2f& position)
{
	this->m_Position = position;
	return *this;
}

SquareBuilder& SquareBuilder::piece(Piece* piece)
{
	this->m_Piece = piece;
}

Square SquareBuilder::build()
{
	return Square(m_Color, m_Coordinates, m_Position, m_Size, m_Piece);
}

SquareBuilder::~SquareBuilder()
{
}
