#include "pch.h"
#include "MoveValidator.h"
#include "Square.h"
#include "Player.h"
#include "Board.h"
#include "Piece.h"
#include "Rook.h"
#include "Pawn.h"
#include <iostream>

MoveValidator::MoveValidator()
{
}

MoveValidator::MoveValidator(Player& player, Player& opponent, Board& board)
{
	m_Player = &player;
	m_Opponent = &opponent;
	m_Board = &board;
}

void MoveValidator::swapPlayers()
{
	Player* temp = std::move(m_Player);
	m_Player = std::move(m_Opponent);
	m_Opponent = std::move(temp);
}

bool MoveValidator::isLegalMove(Square& square, Piece& piece)
{
	if (piece.getColor() != m_Player->getColor())
		swapPlayers();
	bool isLegalMove = false;
	Piece* pieceCaptured = m_Opponent->findPiece(square);
	Square& startSquare = *piece.getSquare();

	if (pieceCaptured)
		m_Opponent->removePiece(pieceCaptured->getId());

	piece.move(square, true);

	if (!m_Player->isChecked(*m_Board))
		isLegalMove = true;
	else
		isLegalMove = false;

	if (pieceCaptured)
		m_Opponent->addPiece(pieceCaptured->getId());
	piece.move(startSquare, true);
	return isLegalMove;
}

bool MoveValidator::castleIsLegal(Square& square, Piece& piece)
{
	if (piece.getColor() != m_Player->getColor())
		swapPlayers();
	sf::Vector2i attackedSquareCoords;
	sf::Vector2i rookStartCoords;
	bool castleIsLegal = false;

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
	if (Colors::isWhite(piece.getColor()))
	{
		attackedSquareCoords.x = 7;
		rookStartCoords.x = 7;
	}
	else
	{
		attackedSquareCoords.x = 0;
		rookStartCoords.x = 0;
	}
	Square* startSquare = m_Board->getSquare(rookStartCoords);
	Square* attackedSquare = m_Board->getSquare(attackedSquareCoords);
	Rook* rook = dynamic_cast<Rook*>(m_Player->findPiece(*m_Board->getSquare(rookStartCoords)));

	if (rook &&
		rook->hasCastle() &&
		!m_Opponent->controlsSquare(*attackedSquare, *m_Board) &&
		!m_Player->isChecked(*m_Board))
	{
		rook->move(*attackedSquare, true);
		castleIsLegal = isLegalMove(square, piece);
		rook->move(*startSquare, true);
	}
	if (castleIsLegal)
	{
		m_Castle = [rook, attackedSquare]() {
			rook->move(*attackedSquare, true);
		};
	}
	return castleIsLegal;
}

bool MoveValidator::enPassantIsLegal(Square& square, Piece& piece)
{
	if (piece.getColor() != m_Player->getColor())
		swapPlayers();
	sf::Vector2i targetCoords = square.getCoordinates();
	sf::Vector2i capturedPawnCoords = Colors::isWhite(piece.getColor()) ?
		sf::Vector2i(targetCoords.x + 1, targetCoords.y) : sf::Vector2i(targetCoords.x - 1, targetCoords.y);

	bool enPassantIsLegal = false;
	Pawn* pawn = dynamic_cast<Pawn*>(m_Opponent->findPiece(*m_Board->getSquare(capturedPawnCoords)));

	if (pawn && pawn->enPassantIsActive())
	{
		m_Opponent->removePiece(pawn->getId());
		enPassantIsLegal = isLegalMove(square, piece);
		m_Opponent->addPiece(pawn->getId());
	}
	if (enPassantIsLegal)
	{
		m_EnPassant = [this, pawn]() {
			pawn->getSquare()->setState(Square::State::IS_FREE);
			m_Opponent->removePiece(pawn->getId());
			pawn->destroy();
		};
	}
	return enPassantIsLegal;
}

void MoveValidator::castle() const
{
	m_Castle();
}

void MoveValidator::enPassant() const
{
	m_EnPassant();
}

void MoveValidator::setPlayers(Player& player, Player& opponent)
{
	m_Player = &player;
	m_Opponent = &opponent;
}

void MoveValidator::setBoard(Board& board)
{
	m_Board = &board;
}