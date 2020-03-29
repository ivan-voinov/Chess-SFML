#pragma once
#include "Piece.h"

class Pawn : public Piece
{
private:
	bool m_HasDoubleMove = true;
	bool movesForward(const Square& square, const Board& board) const;
	bool capturesPiece(const Square& square, const Board& board) const;
	bool doubleMoveIsLegal(const Square& square, const Board& board) const;
	bool freeToMove(const Square& square, const Board& board) const;

public:
	Pawn(const sf::Vector2f& position, const sf::Color& color);
	virtual void onSuccessfulMove() override;
	virtual bool controlsSquare(const Square& square, const Board& board) const override;
	virtual bool isLegalMove(const Square& square, const Board& board) override;
	bool reachedEighthRank() const;
	~Pawn();
};

