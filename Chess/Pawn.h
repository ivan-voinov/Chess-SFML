#pragma once
#include "Piece.h"

class Pawn : public Piece
{
private:
	bool m_HasDoubleMove = true;
	bool m_EnPassantIsActive = false;
	bool movesForward(const Square& square, const Board& board) const;
	bool capturesPiece(const Square& square, const Board& board) const;
	bool doubleMoveIsLegal(const Square& square, const Board& board) const;
	bool freeToMove(const Square& square, const Board& board) const;
	bool enPassant(const Square& square, const Board& board) const;
	bool movesDiagonally(const Square& square) const;

public:
	Pawn(const sf::Vector2f& position, const sf::Color& color);
	virtual void onSuccessfulMove() override;
	virtual bool controlsSquare(const Square& square, const Board& board) const override;
	virtual bool isLegalMove(Square& square, const Board& board) override;
	bool reachedEighthRank() const;
	bool enPassantIsActive() const;
	void deactivateEnPassant();
	~Pawn();
};

