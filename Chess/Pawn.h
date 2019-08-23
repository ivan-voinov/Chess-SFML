#pragma once
#include "Piece.h"


class Pawn : public Piece
{
public:
	Pawn(const sf::Vector2f& position, const sf::Color& color);
	virtual bool isStartingSquare(const sf::Vector2i& coordinates) const;
	virtual bool isLegalMove(const Square& square) override;
	bool reachedEighthRank() const;
	~Pawn();
};

