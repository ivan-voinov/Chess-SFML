#pragma once
#include <string>

class Square;
class Board;

class IObserver
{
public:
	virtual void update(const std::string& event, Square& square, const Board& board) = 0;
	virtual void update(const std::string& event) = 0;
};

