#include "pch.h"
#include "Player.h"
#include "Board.h"


Player::Player(const sf::Color& playerColor)
{
	m_PlayerColor = playerColor;

	if (playerColor == sf::Color::White)
		m_IsPlayerTurn = true;
	else
		m_IsPlayerTurn = false;
}

void Player::addPiece(Square* square)
{
	m_Pieces.push_back(square);
}

void Player::choosePiece(const sf::Vector2i& mousePosition)
{
	for (auto& piece : m_Pieces)
		if (piece->isTriggered(mousePosition))
		{
			if (piece == m_ActivePiece)
			{
				resetActivePiece();
			}
			else
			{
				m_ActivePiece = piece;
			}
		}
}

bool Player::pieceIsChosen() const
{
	if (m_ActivePiece == nullptr)
		return false;
	return true;
}

bool Player::isPlayerTurn() const
{
	return m_IsPlayerTurn;
}

void Player::setBoard(Board* board)
{
	m_Board = board;
}

bool Player::makeMove()
{
	Square* focusedSquare = m_Board->getFocusedSquare();

	if (m_ActivePiece->getPiece()->isLegalMove(*focusedSquare))
	{
		m_ActivePiece->movePiece(*focusedSquare);
		return true;
	}
	else
		return false;
}

void Player::endTurn()
{
	m_IsPlayerTurn = false;
}

void Player::startTurn()
{
	m_Board->resetFocusedSquare();
	resetActivePiece();
	m_IsPlayerTurn = true;
}

void Player::resetActivePiece()
{
	m_ActivePiece = nullptr;
}

void Player::removeGameObject(GameObject* gameObject)
{
	std::vector<Square*>::iterator it;
	it = m_Pieces.begin();
	while (it != m_Pieces.end())
	{
		if ((*it)->getPiece() == gameObject)
			m_Pieces.erase(it);
		else
			++it;
	}
}

Player::~Player()
{
}
