#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(const sf::Vector2f& position, const sf::Color& color);
	virtual void onSuccessfulMove() override;
	virtual bool controlsSquare(const Square& square, const Board& board) const override;
	virtual bool isLegalMove(Square& square, const Board& board) override;
	~Queen();
};

