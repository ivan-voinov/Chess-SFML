#include "pch.h"
#include "MoveValidator.h"
#include "Square.h"
#include "Player.h"
#include "Board.h"
#include "Piece.h"
#include "Rook.h"
#include "Pawn.h"
#include "Colors.h"
#include <iostream>

MoveValidator::MoveValidator()
{
}

MoveValidator::MoveValidator(Player& whitePlayer, Player& blackPlayer, Board& board)
{
	m_WhitePlayer = &whitePlayer;
	m_BlackPlayer = &blackPlayer;
	m_Board = &board;
}

Player& MoveValidator::getPlayer(const sf::Color& color, bool isOpponent) const
{
	if (isOpponent)
		return Colors::isWhite(color) ? *m_BlackPlayer : *m_WhitePlayer;
	else
		return Colors::isWhite(color) ? *m_WhitePlayer : *m_BlackPlayer;
}

Rook* MoveValidator::getCastleRook(const Square& square, const Piece& piece, const Player& currentPlayer) const
{
	sf::Vector2i rookCoords;
	if (square.getCoordinates().y == 6)
		rookCoords.y = 7;

	if (square.getCoordinates().y == 2)
		rookCoords.y = 0;

	if (Colors::isWhite(piece.getColor()))
		rookCoords.x = 7;
	else
		rookCoords.x = 0;

	return dynamic_cast<Rook*>(currentPlayer.findPiece(*m_Board->getSquare(rookCoords)));
}

Square* MoveValidator::getCastleAttackedSquare(const Square& square, const Piece& piece) const
{
	sf::Vector2i attackedSquareCoords;

	if (square.getCoordinates().y == 6)
		attackedSquareCoords.y = 5;

	if (square.getCoordinates().y == 2)
		attackedSquareCoords.y = 3;

	if (Colors::isWhite(piece.getColor()))
		attackedSquareCoords.x = 7;
	else
		attackedSquareCoords.x = 0;

	return m_Board->getSquare(attackedSquareCoords);
}

Pawn* MoveValidator::getCapturedEnPassantPawn(const Square& square, const Piece& piece, const Player& opponent) const
{
	const sf::Vector2i& targetCoords = square.getCoordinates();
	const sf::Vector2i capturedPawnCoords = Colors::isWhite(piece.getColor()) ?
		sf::Vector2i(targetCoords.x + 1, targetCoords.y) : sf::Vector2i(targetCoords.x - 1, targetCoords.y);
	return dynamic_cast<Pawn*>(opponent.findPiece(*m_Board->getSquare(capturedPawnCoords)));
}

bool MoveValidator::isLegalMove(Square& square, Piece& piece)
{
	Player& currentPlayer = getPlayer(piece.getColor(), false);
	Player& opponent = getPlayer(piece.getColor(), true);
	bool isLegalMove = false;
	Piece* pieceCaptured = opponent.findPiece(square);
	Square& startSquare = *piece.getSquare();

	if (pieceCaptured)
		opponent.removePiece(pieceCaptured->getId());

	piece.move(square, true);

	if (!currentPlayer.isChecked())
		isLegalMove = true;
	else
		isLegalMove = false;

	if (pieceCaptured)
		opponent.addPiece(pieceCaptured->getId());
	piece.move(startSquare, true);
	return isLegalMove;
}

bool MoveValidator::castleIsLegal(Square& square, Piece& piece)
{
	Player& currentPlayer = getPlayer(piece.getColor(), false);
	Player& opponent = getPlayer(piece.getColor(), true);
	bool castleIsLegal = false;
	Rook* castleRook = getCastleRook(square, piece, currentPlayer);
	Square* attackedSquare = getCastleAttackedSquare(square, piece);
	Square* startSquare = castleRook->getSquare();

	if (castleRook &&
		castleRook->hasCastle() &&
		!opponent.controlsSquare(*attackedSquare) &&
		!currentPlayer.isChecked())
	{
		castleRook->move(*attackedSquare, true);
		castleIsLegal = isLegalMove(square, piece);
		castleRook->move(*startSquare, true);
	}
	return castleIsLegal;
}

bool MoveValidator::enPassantIsLegal(Square& square, Piece& piece)
{
	Player& currentPlayer = getPlayer(piece.getColor(), false);
	Player& opponent = getPlayer(piece.getColor(), true);

	bool enPassantIsLegal = false;
	Pawn* pawn = getCapturedEnPassantPawn(square, piece, opponent);

	if (pawn && pawn->enPassantIsActive())
	{
		opponent.removePiece(pawn->getId());
		enPassantIsLegal = isLegalMove(square, piece);
		opponent.addPiece(pawn->getId());
	}
	return enPassantIsLegal;
}

void MoveValidator::castle(Square& square, Piece& piece) const
{
	Player& player = getPlayer(piece.getColor(), false);
	Rook* castleRook = getCastleRook(square, piece, player);
	Square* attackedSquare = getCastleAttackedSquare(square, piece);
	castleRook->move(*attackedSquare, false);
}

void MoveValidator::enPassant(Square& square, Piece& piece) const
{
	Player& opponent = getPlayer(piece.getColor(), true);
	Pawn* pawn = getCapturedEnPassantPawn(square, piece, opponent);
	pawn->getSquare()->setState(Square::State::IS_FREE);
	opponent.removePiece(pawn->getId());
	pawn->destroy();
}

void MoveValidator::setPlayers(Player& whitePlayer, Player& blackPlayer)
{
	m_WhitePlayer = &whitePlayer;
	m_BlackPlayer = &blackPlayer;
}

void MoveValidator::setBoard(Board& board)
{
	m_Board = &board;
}

void MoveValidator::onPawnPromotionTriggered(Square& square, Piece& piece)
{
	Player& currentPlayer = getPlayer(piece.getColor(), false);
	currentPlayer.onPawnPromotionTriggered(square, piece);
}