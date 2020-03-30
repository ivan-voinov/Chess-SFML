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

	if (playerColor == Colors::getColor(Colors::Names::WHITE))
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
	m_PiecesIds.erase(std::remove_if(
		m_PiecesIds.begin(),
		m_PiecesIds.end(),
		[capturedPieceId](int gmObjId) {return gmObjId == capturedPieceId;}));
}

bool Player::isChecked(const Player& opponent, const Board& board) const
{
	std::vector<Piece*> opponentPieces = GameManager::getInstance().getGameObjects<Piece>(opponent.m_PiecesIds);
	Piece* king = getKing();
	for (const auto& piece : opponentPieces)
	{
		if (piece->controlsSquare(*king->getSquare(), board))
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

bool Player::controlsSquare(const Square& square, const Board& board) const
{
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	for (const auto& piece : pieces)
	{
		if (piece->controlsSquare(square, board))
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

bool Player::makeMove(Square& square, Player& opponent, const Board& board)
{
	Piece* focusedPiece = GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId);
	Piece* pieceCaptured = opponent.findPiece(square);
	Square& startSquare = *focusedPiece->getSquare();

	//Capture the piece
	if (pieceCaptured)
		opponent.removePiece(pieceCaptured->getId());

	//Make the move
	focusedPiece->move(square);
	resetMoveState(startSquare);

	//If making a move does not lead to a checked state, complete the move
	if (!isChecked(opponent, board))
	{
		focusedPiece->onSuccessfulMove();
		if (pieceCaptured)
			pieceCaptured->destroy();
		return true;
	}
	//If making a move leads to a checked state, revert the move because it's illegal
	else
	{
		focusedPiece->move(startSquare);
		if (pieceCaptured)
			opponent.addPiece(pieceCaptured->getId());
		return false;
	}
}

void Player::processTurn(Player& opponent, Board& board, sf::RenderWindow& window)
{
	Piece* triggeredPiece = getTriggeredPiece(sf::Mouse::getPosition(window));
	Square* triggeredSquare = board.getTriggeredSquare(sf::Mouse::getPosition(window));
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	Piece* focusedPiece = GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId);

	if (!pieceIsChosen() && triggeredPiece)
	{
		if (m_FocusedPieceId == triggeredPiece->getId())
		{
			resetMoveState(*focusedPiece->getSquare());
		}
		else
		{
			m_FocusedPieceId = triggeredPiece->getId();
			highlightSquare(*triggeredPiece->getSquare());
		}
	}
	else
	{ 
		if (triggeredSquare 
			&& focusedPiece->isLegalMove(*board.getTriggeredSquare(sf::Mouse::getPosition(window)), board)
			&& makeMove(*triggeredSquare, opponent, board))
		{
				switchTurn(opponent);
		}
		else
		{
			resetMoveState(*focusedPiece->getSquare());
		}
	}
}

void Player::switchTurn(Player& opponent)
{
	m_IsPlayerTurn = !m_IsPlayerTurn;
	opponent.m_IsPlayerTurn = !opponent.isPlayerTurn();
}

void Player::resetMoveState(Square& square)
{
	m_FocusedPieceId = -1;
	square.resetColor();
}

void Player::highlightSquare(Square& square)
{
	square.setColor(Colors::getColor(Colors::Names::GREEN));
}

Player::~Player()
{
}
