#pragma once
#include "Piece.h"

class King : public Piece
{
private:
	bool m_HasCastle = true;

public:
	King(const sf::Vector2f& position, const sf::Color& color);
	King(const sf::Vector2f& position, int squareId, const sf::Color& color);
	bool isCastling(const Square& square) const;
	void move(Square& square, bool isMockingMove) override;
	void onSuccessfulMove() override;
	bool controlsSquare(const Square& square) const override;
	bool isLegalMove(Square& square) override;
	~King();
};

