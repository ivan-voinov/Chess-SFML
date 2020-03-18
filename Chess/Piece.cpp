#include "pch.h"
#include "Piece.h"
#include "Square.h"
#include "GameManager.h"


Piece::Piece(const sf::Vector2f& position, const sf::Color& color)
{
	this->m_Color = color;

	m_PieceSprite.setOrigin(m_PieceSprite.getGlobalBounds().width / 2, m_PieceSprite.getGlobalBounds().height / 2);
	m_PieceSprite.setColor(color);
	m_PieceSprite.setPosition(position);
}


void Piece::swapCoordinates(sf::Vector2i& coords1, sf::Vector2i& coords2) const
{
	sf::Vector2i temp = coords1;
	coords1 = coords2;
	coords2 = temp;
}

bool Piece::controlsLine(
	const Player& player,
	const Player& opponent,
	const sf::Vector2i& coords1,
	const sf::Vector2i& coords2
) const
{
	int xDifference = abs(coords1.x - coords2.x);
	int yDifference = abs(coords1.y - coords2.y);
	sf::Vector2i startPoint(coords1.x, coords1.y);
	sf::Vector2i endPoint(coords2.x, coords2.y);
	bool isVertical = false;

	if (!((xDifference == 0 && yDifference > 0) || (yDifference == 0 && xDifference > 0)))
	{
		return false;
	}
	if (coords1.x < coords2.x && coords1.y == coords2.y)
	{
		isVertical = true;
	}
	if (coords1.x > coords2.x && coords1.y == coords2.y)
	{
		isVertical = true;
		swapCoordinates(startPoint, endPoint);
	}
	if (coords1.x == coords2.x && coords1.y < coords2.y)
	{
		isVertical = false;
	}
	if (coords1.x == coords2.x && coords1.y > coords2.y)
	{
		isVertical = false;
		swapCoordinates(startPoint, endPoint);
	}
	int i = isVertical ? startPoint.x + 1 : startPoint.x;
	int j = isVertical ? startPoint.y : startPoint.y + 1;
	if (isVertical)
	{
		for (i; i < endPoint.x; i++)
			if (opponent.hasPieceOnSquare(sf::Vector2i(i, j)) || player.hasPieceOnSquare(sf::Vector2i(i, j)))
				return false;
	}
	else
	{
		for (j; j < endPoint.y; j++)
			if (opponent.hasPieceOnSquare(sf::Vector2i(i, j)) || player.hasPieceOnSquare(sf::Vector2i(i, j)))
				return false;
	}
	return true;
}

bool Piece::controlsDiagonal(
	const Player& player,
	const Player& opponent,
	const sf::Vector2i& coords1,
	const sf::Vector2i& coords2
) const
{
	bool isMainDiagonal = false;
	int xDifference = abs(coords1.x - coords2.x);
	int yDifference = abs(coords1.y - coords2.y);
	sf::Vector2i startPoint(coords1.x, coords1.y);
	sf::Vector2i endPoint(coords2.x, coords2.y);

	if ((xDifference != yDifference) || xDifference == 0)
	{
		return false;
	}
	if (coords1.x < coords2.x && coords1.y < coords2.y)
	{
		isMainDiagonal = true;
	}
	if (coords1.x > coords2.x && coords1.y > coords2.y)
	{
		isMainDiagonal = true;
		swapCoordinates(startPoint, endPoint);
	}
	if (coords1.x < coords2.x && coords1.y > coords2.y)
	{
		isMainDiagonal = false;
	}
	if (coords1.x > coords2.x && coords1.y < coords2.y)
	{
		isMainDiagonal = false;
		swapCoordinates(startPoint, endPoint);
	}

	int j = startPoint.y;
	for (int i = startPoint.x + 1; i < endPoint.x; i++)
	{
		j = isMainDiagonal ? (j + 1) : (j - 1);
		if (opponent.hasPieceOnSquare(sf::Vector2i(i, j)) || player.hasPieceOnSquare(sf::Vector2i(i, j)))
			return false;
	}
	return true;
}

const sf::Color& Piece::getColor() const
{
	return m_Color;
}

void Piece::setSquare(int squareId)
{
	m_SquareId = squareId;
}

Square* Piece::getSquare() const
{
	return GameManager::getInstance().getGameObject<Square>(m_SquareId);
}

void Piece::setSquareColor(const sf::Color& color)
{
	GameManager::getInstance().getGameObject<Square>(m_SquareId)->setColor(color);
}

bool Piece::canBeCaptured(const Piece& piece) const
{
	if (piece.getColor() != this->m_Color)
		return true;
	return false;
}

void Piece::move(Square& square)
{
	m_SquareId = square.getId();
	m_PieceSprite.setPosition(square.getPosition());
}

void Piece::resize(const double squareSize)
{
	m_PieceSprite.setScale(squareSize / m_PieceTexture.getSize().x, squareSize / m_PieceTexture.getSize().y);
}

void Piece::onCaptured()
{
	destroy();
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_PieceSprite, states);
}

bool Piece::isLegalMove(const Square& square, const Player& player, const Player& opponent)
{
	return player.findPiece(square) == nullptr;
}

bool Piece::isTriggered(const sf::Vector2i & mousePosition) const
{
	return m_PieceSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition)) ? true : false;
}

Piece::~Piece()
{
}
