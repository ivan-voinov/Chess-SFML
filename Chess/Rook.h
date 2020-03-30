#pragma once
#include "Piece.h"

class Rook : public Piece
{
private:
	bool m_HasCastle = true;

public:
	Rook(const sf::Vector2f& position, const sf::Color& color);
	virtual void onSuccessfulMove() override;
	virtual bool controlsSquare(const Square& square, const Board& board) const override;
	virtual bool isLegalMove(const Square& square, const Board& board) override;
	~Rook();
};

