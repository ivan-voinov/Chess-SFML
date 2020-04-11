#pragma once
#include "Piece.h"

class Pawn : public Piece
{
private:
	bool m_HasDoubleMove = true;
	bool m_EnPassantIsActive = false;
	int m_EnPassantSquareId = -1;

	bool moveForwardIsLegal(const Square& square, const Board& board) const;
	bool capturesPiece(const Square& square, const Board& board) const;
	bool doubleMoveIsLegal(const Square& square, const Board& board) const;
	bool freeToMove(const Square& square, const Board& board) const;
	bool enPassant(const Square& square, const Board& board) const;
	bool movesDiagonally(const Square& square) const;

public:
	Pawn(const sf::Vector2f& position, const sf::Color& color);
	Pawn(const sf::Vector2f& position, int squareId, const sf::Color& color);
	virtual void move(Square& square, bool isMockingMove) override;
	virtual void onSuccessfulMove() override;
	virtual bool controlsSquare(const Square& square, const Board& board) const override;
	virtual bool isLegalMove(Square& square, const Board& board) override;
	bool canBePromoted(const Square& square) const;
	bool enPassantIsActive() const;
	void deactivateEnPassant();
	~Pawn();
};

