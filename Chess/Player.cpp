#include "pch.h"
#include "Player.h"
#include "Square.h"
#include <vector>
#include <string>
#include "Piece.h"
#include "King.h"
#include "Rook.h"
#include "Board.h"
#include "GameManager.h"


Player::Player(const sf::Color& playerColor)
{
	m_PlayerColor = playerColor;

	if (Colors::isWhite(m_PlayerColor))
		m_IsPlayerTurn = true;
	else
		m_IsPlayerTurn = false;
}

void Player::update(const std::string& event, Square& square, const Board& board)
{
	Piece* focusedPiece = GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId);
	sf::Vector2i attackedSquareCoords;
	sf::Vector2i rookStartCoords;

	if (!event.compare("CASTLE"))
	{
		if (square.getCoordinates().y == 6)
		{
			attackedSquareCoords.y = 5;
			rookStartCoords.y = 7;
		}
		if (square.getCoordinates().y == 2)
		{
			attackedSquareCoords.y = 3;
			rookStartCoords.y = 0;
		}
		if (Colors::isWhite(m_PlayerColor))
		{
			attackedSquareCoords.x = 7;
			rookStartCoords.x = 7;
		}
		else
		{
			attackedSquareCoords.x = 0;
			rookStartCoords.x = 0;
		}
		Rook* rook = dynamic_cast<Rook*>(findPiece(*board.getSquare(rookStartCoords)));

		if (castlingIsLegal(square, board, *focusedPiece, rook, attackedSquareCoords))
			rook->move(*board.getSquare(attackedSquareCoords));
	}
	if (!event.compare("EN_PASSANT"))
	{

	}
	if (!event.compare("PAWN_TRANSFORMATION"))
	{

	}
}

bool Player::castlingIsLegal(
	Square& square,
	const Board& board,
	Piece& focusedPiece,
	Rook* rook,
	const sf::Vector2i attackedSquareCoords)
{
	return
		rook &&
		rook->hasCastle() &&
		!m_Opponent->controlsSquare(*board.getSquare(attackedSquareCoords), board) &&
		!isChecked(board) &&
		makeMove(square, board, focusedPiece);
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

bool Player::isChecked(const Board& board) const
{
	Piece* king = getKing();
	return m_Opponent->controlsSquare(*king->getSquare(), board);
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

void Player::attachOpponent(Player& opponent)
{
	m_Opponent = &opponent;
}

void Player::setKing(int kingId)
{
	m_KingId = kingId;
}

bool Player::controlsSquare(Square& square, const Board& board)
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

bool Player::makeMove(Square& square, const Board& board, Piece& focusedPiece)
{
	Piece* pieceCaptured = m_Opponent->findPiece(square);
	Square& startSquare = *focusedPiece.getSquare();

	//Capture the piece
	if (pieceCaptured)
		m_Opponent->removePiece(pieceCaptured->getId());

	//Make the move
	focusedPiece.move(square);

	//If making a move does not lead to a checked state, complete the move
	if (!isChecked(board))
	{
		if (pieceCaptured)
			pieceCaptured->destroy();
		onSuccessfulMove(startSquare, focusedPiece);
		return true;
	}
	//If making a move leads to a checked state, revert the move because it's illegal
	else
	{
		focusedPiece.move(startSquare);
		if (pieceCaptured)
			m_Opponent->addPiece(pieceCaptured->getId());
		onFailedMove(startSquare);
		return false;
	}
}

void Player::onSuccessfulMove(Square& square, Piece& piece)
{
	piece.onSuccessfulMove();
	resetMoveState(square);
	switchTurn();
}

void Player::onFailedMove(Square& square)
{
	resetMoveState(square);
}

void Player::processTurn(Board& board, sf::RenderWindow& window)
{
	Piece* triggeredPiece = getTriggeredPiece(sf::Mouse::getPosition(window));
	Square* triggeredSquare = board.getTriggeredSquare(sf::Mouse::getPosition(window));
	std::vector<Piece*> pieces = GameManager::getInstance().getGameObjects<Piece>(m_PiecesIds);
	Piece* focusedPiece = GameManager::getInstance().getGameObject<Piece>(m_FocusedPieceId);

	if (!pieceIsChosen())
	{
		if (triggeredPiece)
		{
			choosePiece(board, *triggeredPiece);
		}
	}
	else
	{ 
		if (triggeredSquare && focusedPiece->isLegalMove(*triggeredSquare, board))
		{
			makeMove(*triggeredSquare, board, *focusedPiece);
		}
		else
		{
			onFailedMove(*focusedPiece->getSquare());
		}
	}
}

void Player::choosePiece(const Board& board, Piece& triggeredPiece)
{
	m_FocusedPieceId = triggeredPiece.getId();
	highlightSquare(*triggeredPiece.getSquare());
}

void Player::switchTurn()
{
	m_IsPlayerTurn = !m_IsPlayerTurn;
	m_Opponent->m_IsPlayerTurn = !m_Opponent->isPlayerTurn();
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
