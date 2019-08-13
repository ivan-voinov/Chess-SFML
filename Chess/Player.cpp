#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <vector>


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
			if (piece == m_FocusedPiece)
			{
				resetFocusedPiece();
			}
			else
			{
				piece->setColor(Square::greenColor);
				m_FocusedPiece = piece;
			}
		}
}

bool Player::pieceIsChosen() const
{
	if (m_FocusedPiece == nullptr)
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

	if (m_FocusedPiece->getPiece()->isLegalMove(*focusedSquare))
	{
		m_FocusedPiece->movePiece(*focusedSquare);
		removeGameObject(m_FocusedPiece->getPiece());
		addPiece(focusedSquare);
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
	m_IsPlayerTurn = true;
}

void Player::resetFocusedPiece()
{
	m_FocusedPiece->setColor(m_FocusedPiece->getInitialColor());
	m_FocusedPiece = nullptr;
}

void Player::removeGameObject(GameObject* gameObject)
{
	std::vector<Square*>::iterator it;
	it = m_Pieces.begin();
	while (it != m_Pieces.end())
	{
		if ((*it)->getPiece() == gameObject)
		{
			m_Pieces.erase(it);
			break;
		}
		++it;
	}
}

Player::~Player()
{
}
