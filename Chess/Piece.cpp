#include "pch.h"
#include "Piece.h"
#include "Square.h"


Piece::Piece(const sf::Vector2f& position, const sf::Vector2i coordinates, const sf::Color& color)
{
	this->m_Color = color;
	this->m_Coordinates = coordinates;

	m_PieceSprite.setOrigin(m_PieceSprite.getGlobalBounds().width / 2, m_PieceSprite.getGlobalBounds().height / 2);
	m_PieceSprite.setColor(color);
	m_PieceSprite.setPosition(position);

}

const sf::Color& Piece::getColor() const
{
	return m_Color;
}

bool Piece::canBeCaptured(const Piece &piece) const
{
	if (piece.getColor() != this->m_Color)
		return true;
	return false;
}

void Piece::move(Square& square)
{
	m_Coordinates = square.getCoordinates();
	m_PieceSprite.setPosition(square.getPosition());
}

void Piece::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_PieceSprite, states);
}

Piece::~Piece()
{
}
