#pragma once

class Square;
class Piece;

class IMoveValidator
{
public:
	virtual bool isLegalMove(Square& square, Piece& piece) = 0;
	virtual bool castleIsLegal(Square& square, Piece& piece) = 0;
	virtual bool enPassantIsLegal(Square& square, Piece& piece) = 0;
	virtual void castle(Square& square, Piece& piece) const = 0;
	virtual void enPassant(Square& square, Piece& piece) const = 0;
	virtual void onPawnPromotionTriggered(Square& square, Piece& piece) = 0;
};

