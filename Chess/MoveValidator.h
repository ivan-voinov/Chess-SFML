#pragma once
#include <functional>

class Player;
class Board;
class Square;
class Piece;

class MoveValidator
{
private:
	Player* m_Player = nullptr;
	Player* m_Opponent = nullptr;
	Board* m_Board = nullptr;
	void swapPlayers();
	std::function<void()> m_Castle;
	std::function<void()> m_EnPassant;
	
public:
	MoveValidator();
	MoveValidator(Player& player, Player& opponent, Board& board);
	bool isLegalMove(Square& square, Piece& piece);
	bool castleIsLegal(Square& square, Piece& piece);
	bool enPassantIsLegal(Square& square, Piece& piece);
	void castle() const;
	void enPassant() const;
	void setPlayers(Player& player, Player& opponent);
	void setBoard(Board& board);
};

