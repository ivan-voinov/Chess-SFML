#include "pch.h"
#include "Piece.h"
#include "Square.h"


Piece::Piece(const sf::Vector2f& position, const sf::Color& color)
{
	this->m_Color = color;

	m_PieceSprite.setOrigin(m_PieceSprite.getGlobalBounds().width / 2, m_PieceSprite.getGlobalBounds().height / 2);
	m_PieceSprite.setColor(color);
	m_PieceSprite.setPosition(position);

}

const sf::Color& Piece::getColor() const
{
	return m_Color;
}

void Piece::setSquare(Square& square)
{
	m_Square = &square;
}

Square* Piece::getSquare() const
{
	return m_Square;
}

void Piece::setSquareColor(const sf::Color& color)
{
	m_Square->setColor(color);
}

bool Piece::canBeCaptured(const Piece& piece) const
{
	if (piece.getColor() != this->m_Color)
		return true;
	return false;
}

void Piece::move(Square& square)
{
	m_Square = &square;
	m_PieceSprite.setPosition(square.getPosition());
}

void Piece::resize(const double squareSize)
{
	m_PieceSprite.setScale(squareSize / m_PieceTexture.getSize().x, squareSize / m_PieceTexture.getSize().y);
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_PieceSprite, states);
}

bool Piece::isTriggered(const sf::Vector2i & mousePosition) const
{
	//If the mouse is inside the piece sprite, return true (false otherwise)
	if (m_PieceSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
		return true;
	return false;
}

Piece::~Piece()
{
}
