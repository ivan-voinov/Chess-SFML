#pragma once
#include "Piece.h"


class Pawn : public Piece
{
private:
	bool m_HasDoubleMove = true;
	bool movesForward(const Square& square, const Player& player, const Player& opponent) const;
	bool capturesPiece(const Square& square, const Player& player, const Player& opponent) const;
	bool doubleMoveIsBlocked(const Square& targetSquare, const Player& player, const Player& opponent) const;
	bool freeToMove(const Square& targetSquare, const Player& player, const Player& opponent) const;

public:
	Pawn(const sf::Vector2f& position, const sf::Color& color);
	virtual bool controlsSquare(const Square& square, const Player& player, const Player& opponent) const override;
	virtual bool isLegalMove(const Square& square, const Player& player, const Player& opponent) override;
	bool reachedEighthRank() const;
	~Pawn();
};

