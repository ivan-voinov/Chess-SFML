#include "pch.h"
#include "SquareBuilder.h"


SquareBuilder::SquareBuilder(const sf::Vector2i& coordinates, float size)
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

SquareBuilder& SquareBuilder::state(const Square::State& state)
{
	this->m_State = state;
	return *this;
}

Square SquareBuilder::build()
{
	return Square(m_Color, m_Coordinates, m_Position, m_Size, m_State);
}

SquareBuilder::~SquareBuilder()
{
}
