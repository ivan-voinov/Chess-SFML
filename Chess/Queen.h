#pragma once
#include "Piece.h"

class Bishop;
class Rook;

class Queen : public Piece
{
public:
	Queen(const sf::Vector2f& position, const sf::Color& color);
	virtual bool controlsSquare(const Square& square, const Player& player, const Player& opponent) const override;
	virtual bool isLegalMove(const Square& square, const Player& player, const Player& opponent) override;
	~Queen();
};

