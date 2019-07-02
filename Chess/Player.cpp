#include "pch.h"
#include "Player.h"


Player::Player()
{
}

void Player::addPiece(Square* square)
{
	m_Pieces.push_back(square);
}

void Player::removePiece(Square* square)
{
	std::vector<Square*>::iterator it;
	it = m_Pieces.begin();
	while (it != m_Pieces.end())
	{
		if (*it == square)
			m_Pieces.erase(it);
		++it;
	}
}

bool Player::choosePiece(const sf::Vector2i& mousePosition)
{
	for (auto piece : m_Pieces)
		if (piece->isTriggered(mousePosition))
		{
			m_ActivePiece = piece;
			return true;
		}
	return false;
}


Player::~Player()
{
}
