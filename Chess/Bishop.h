#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(const sf::Vector2f& position, const sf::Color& color);
	virtual void onSuccessfulMove() override;
	virtual bool controlsSquare(const Square& square, const Board& board) const override;
	virtual bool isLegalMove(const Square& square, const Board& board) override;
	~Bishop();
};

