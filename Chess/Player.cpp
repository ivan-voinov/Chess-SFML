#include "pch.h"
#include "Player.h"
#include "Square.h"
#include "Piece.h"
#include "King.h"
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

Piece* Player::getTriggeredPiece(const sf::Vector2i& mousePosition)
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	Piece* focusedPiece = GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId);
	for (auto& piece : pieces)
	{
		if (piece->isTriggered(mousePosition))
			return piece;
	}
	return nullptr;
}

void Player::resetFocusedSquare()
{
	m_FocusedSquareId = -1;
}

void Player::checkKing()
{
	m_Checked = true;
	King* king = GameManager::getInstance().getGameObject<King>(m_KingId);
	//TODO: checked highlight
}

void Player::uncheckKing()
{
	m_Checked = false;
	King* king = GameManager::getInstance().getGameObject<King>(m_KingId);
	//TODO: remove checked highlight
}

void Player::removePiece(int capturedPieceId)
{
	//TODO
}

bool Player::squareIsChosen() const
{
	return m_FocusedSquareId == -1;
}

bool Player::isChecked(const Player& opponent) const
{
	std::vector<Piece*> opponentPieces = GameManager::getInstance().getGameObjects<Piece>(opponent.m_PiecesIds);
	Piece* king = getKing();
	for (const auto& piece : opponentPieces)
	{
		if (piece->controlsSquare(*king->getSquare(), *this, opponent))
			return true;
	}
	return false;
}

Piece* Player::findPiece(const Square& square) const
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	for (auto& piece : pieces)
	{
		if (piece->getSquare() == &square)
			return piece;
	}
	return nullptr;
}

Piece* Player::getKing() const
{
	return GameManager::getInstance().getGameObject<Piece>(m_KingId);
}

void Player::setKing(int kingId)
{
	m_KingId = kingId;
}

bool Player::hasPieceOnSquare(const sf::Vector2i& squareCoordinates) const
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	for (const auto& piece : pieces)
	{
		if (piece->getSquare()->getCoordinates() == squareCoordinates)
			return true;
	}
	return false;
}

bool Player::controlsSquare(const Square& square, const Player& opponent) const
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	for (const auto& piece : pieces)
	{
		if (piece->controlsSquare(square, *this, opponent))
			return true;
	}
	return false;
}

void Player::resizePieces(const double squareSize)
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	for (auto& piece : pieces)
		piece->resize(squareSize);
}

bool Player::pieceIsChosen() const
{
	return m_FocusedPieceId != -1;
}

bool Player::isPlayerTurn() const
{
	return m_IsPlayerTurn;
}

void Player::makeMove(Square& square, Player& opponent)
{
	Piece* focusedPiece = GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId);
	//Move the focused piece to the focused square
	Piece* pieceCaptured = opponent.findPiece(square);
	if (pieceCaptured)
	{
		pieceCaptured->destroy();
		removePiece(pieceCaptured->getId());
	}
	focusedPiece->move(square);
}

void Player::processTurn(Player& opponent, Board& board, sf::RenderWindow& window)
{
	Piece* triggeredPiece = getTriggeredPiece(sf::Mouse::getPosition(window));
	Square* triggeredSquare = board.getTriggeredSquare(sf::Mouse::getPosition(window));
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	Piece* focusedPiece = GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId);
	Square* focusedSquare = GameManager::getInstance().getGameObject<Square>(m_FocusedSquareId);

	if (!pieceIsChosen())
	{
		if (triggeredPiece)
		{
			if (m_FocusedPieceId == triggeredPiece->getId())
			{
				resetFocusedPieceColor();
				resetFocusedPiece();
			}
			else
			{
				m_FocusedPieceId = triggeredPiece->getId();
				highlightFocusedPiece();
			}
		}
	}
	else
	{ 
		if (triggeredSquare)
		{
			//TODO: check if the square is legal
			if (focusedPiece->isLegalMove(*board.getTriggeredSquare(sf::Mouse::getPosition(window)), *this, opponent))
			{
				resetFocusedPieceColor();
				makeMove(*triggeredSquare, opponent);
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

void Player::highlightFocusedPiece()
{
	Piece* focusedPiece = GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId);
	focusedPiece->setSquareColor(Colors::getInstance().getColor(Colors::ColorNames::GREEN));
}

Player::~Player()
{
}
