#include "pch.h"
#include "Player.h"
#include "Square.h"
#include "Piece.h"
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

void Player::addPiece(int pieceId)
{
	m_PiecesIds.push_back(pieceId);
}

void Player::choosePiece(const sf::Vector2i& mousePosition)
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	Piece* focusedPiece = GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId);
	for (auto& piece : pieces)
	{
		if (piece->isTriggered(mousePosition))
		{
			if (piece == focusedPiece)
			{
				focusedPiece->getSquare()->resetColor();
				resetFocusedPiece();
			}
			else
			{
				piece->setSquareColor(Colors::getInstance().getColor(Colors::ColorNames::GREEN));
				m_FocusedPieceId = piece->getId();
			}
		}
	}
}

Piece* Player::findPieceBySquare(const Square& square) const
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	for (auto& piece : pieces)
	{
		if (piece->getSquare() == &square)
			return piece;
	}
	//If the player doesn't control the square
	return nullptr;
}

void Player::resizePieces(const double squareSize)
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	for (auto& piece : pieces)
		piece->resize(squareSize);
}

bool Player::pieceIsChosen() const
{
	return m_FocusedPieceId == -1 ? false : true;
}

bool Player::isPlayerTurn() const
{
	return m_IsPlayerTurn;
}

bool Player::isLegalMove(Square& square) const
{
	Piece* focusedPiece = GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId);
	return focusedPiece->isLegalMove(square) ? true : false;
}

void Player::makeMove(Square& square)
{
	Piece* focusedPiece = GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId);
	//Move the focused piece to the focused square
	focusedPiece->move(square);
}

void Player::processTurn(Player& opponent, Board& board, sf::RenderWindow& window)
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	Piece* focusedPiece = GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId);
	if (!pieceIsChosen())
	{
		choosePiece(sf::Mouse::getPosition(window));
	}
	else
	{
		if (board.chooseSquareForPiece(sf::Mouse::getPosition(window)))
		{
			//TODO: check if the square is legal
			if (focusedPiece->isLegalMove(*board.getFocusedSquare()))
			{
				resetFocusedPieceColor();
				makeMove(*board.getFocusedSquare());
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
	opponent.m_IsPlayerTurn = !opponent.isPlayerTurn();
}

void Player::resetFocusedPiece()
{
	m_FocusedPieceId = -1;
}

void Player::resetFocusedPieceColor()
{
	Piece* focusedPiece = GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId);
	//Reset the color of the square with selected piece
	focusedPiece->getSquare()->resetColor();
}

Player::~Player()
{
}
