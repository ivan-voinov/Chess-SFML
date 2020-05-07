#pragma once

class Square;

class ILineValidator
{
public:
	virtual bool diagonalIsFree(const Square& startSquare, const Square& destSquare) const = 0;
	virtual bool LineIsFree(const Square& startSquare, const Square& destSquare) const = 0;
};

