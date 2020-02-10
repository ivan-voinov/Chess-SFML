#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <vector>
#include "GameManager.h"


Player::Player(const sf::Color& playerColor)
{
	m_PlayerColor = playerColor;

	if (playerColor == Colors::getInstance().getColor(Colors::ColorNames::WHITE))
		m_IsPlayerTurn = true;
	else
		m_IsPlayerTurn = false;
}

void Player::addPiece(std::unique_ptr<Piece> piece)
{
	m_Pieces.push_back(std::move(piece));
}

void Player::registerGameObjects()
{
	for (auto& piece : m_Pieces)
		GameManager::getInstance().addGameObject(piece.get());
}

void Player::choosePiece(const sf::Vector2i& mousePosition)
{
	for (auto& piece : m_Pieces)
	{
		if (piece->isTriggered(mousePosition))
		{
			if (piece.get() == m_FocusedPiece)
			{
				m_FocusedPiece->getSquare()->resetColor();
				resetFocusedPiece();
			}
			else
			{
				piece->setSquareColor(Colors::getInstance().getColor(Colors::ColorNames::GREEN));
				m_FocusedPiece = piece.get();
			}
		}
	}
}

Piece* Player::findPieceBySquare(const Square& square) const
{
	for (auto& piece : m_Pieces)
	{
		if (piece->getSquare() == &square)
			return piece.get();
	}

	//If the player doesn't control the square
	return nullptr;
}

void Player::resizePieces(const double squareSize)
{
	for (auto& piece : m_Pieces)
	{
		piece->resize(squareSize);
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

bool Player::isLegalMove(Square& square) const
{
	if (m_FocusedPiece->isLegalMove(square))
		return true;

	return false;
}

void Player::makeMove(Square& square)
{
	//Move the focused piece to the focused square
	m_FocusedPiece->move(square);
}

void Player::processTurn(Player& opponent, Board& board, sf::RenderWindow& window)
{
	if (!pieceIsChosen())
	{
		choosePiece(sf::Mouse::getPosition(window));
	}
	else
	{
		if (board.chooseSquareForPiece(sf::Mouse::getPosition(window)))
		{
			//TODO: check if the square is legal
			if (m_FocusedPiece->isLegalMove(board.getFocusedSquare()))
			{
				resetFocusedPieceColor();
				makeMove(board.getFocusedSquare());
				resetFocusedPiece();
				switchTurn(opponent);
			}
			else
			{
				resetFocusedPieceColor();
				resetFocusedPiece();
			}
		}
	}
}

void Player::switchTurn(Player& opponent)
{
	m_IsPlayerTurn = !m_IsPlayerTurn;
	opponent.isPlayerTurn = !opponent.isPlayerTurn;
}

void Player::resetFocusedPiece()
{
	m_FocusedPiece = nullptr;
}

void Player::resetFocusedPieceColor()
{
	//Reset the color of the square with selected piece
	m_FocusedPiece->getSquare()->resetColor();
}

void Player::removeGameObject(GameObject* gameObject)
{
	std::vector<std::unique_ptr<Piece>>::iterator it;
	it = m_Pieces.begin();
	while (it != m_Pieces.end())
	{
		if ((*it).get() == gameObject)
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
