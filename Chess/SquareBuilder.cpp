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

SquareBuilder& SquareBuilder::free(bool free)
{
	this->m_Free = free;
	return *this;
}

SquareBuilder& SquareBuilder::timesAttacked(int timesAttacked)
{
	this->m_TimesAttacked = timesAttacked;
	return *this;
}

SquareBuilder& SquareBuilder::piece(std::unique_ptr<Piece> piece)
{
	this->m_Piece = std::move(piece);
	piece = nullptr;
	return *this;
}

Square SquareBuilder::build()
{
	return Square(m_Color, m_Coordinates, m_Position, std::move(m_Piece), m_Size, m_Free, m_TimesAttacked);
}

SquareBuilder::~SquareBuilder()
{
}
