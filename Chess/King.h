#pragma once
#include "Piece.h"

class King : public Piece
{
private:
	bool m_HasCastle = true;

public:
	King(const sf::Vector2f& position, const sf::Color& color);
	bool isCastling(const Square& square, const Board& board) const;
	virtual void onSuccessfulMove() override;
	virtual bool controlsSquare(const Square& square, const Board& board) const override;
	virtual bool isLegalMove(Square& square, const Board& board) override;
	~King();
};

