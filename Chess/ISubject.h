#pragma once
#include "IObserver.h"

class Square;
class Board;

class ISubject
{
public:
	virtual void registerObserver(IObserver* observer) = 0;
	virtual void removeObserver(IObserver* observer) = 0;
	virtual void notifyObserver(const std::string& event, Square& square, const Board& board) const = 0;
};

