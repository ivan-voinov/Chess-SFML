#pragma once
#include <functional>
#include <SFML/Graphics.hpp>

class Player;
class Board;
class Square;
class Piece;
class Rook;
class Pawn;

class MoveValidator
{
private:
	Player* m_WhitePlayer = nullptr;
	Player* m_BlackPlayer = nullptr;
	Board* m_Board = nullptr;

	Player& getPlayer(const sf::Color& color, bool isOpponent) const;
	Rook* getCastleRook(const Square& square, const Piece& piece, const Player& currentPlayer) const;
	Square* getCastleAttackedSquare(const Square& square, const Piece& piece) const;
	Pawn* getCapturedEnPassantPawn(const Square& square, const Piece& piece, const Player& opponent) const;
	
public:
	MoveValidator();
	MoveValidator(Player& whitePlayer, Player& blackPlayer, Board& board);
	bool isLegalMove(Square& square, Piece& piece);
	bool castleIsLegal(Square& square, Piece& piece);
	bool enPassantIsLegal(Square& square, Piece& piece);
	void castle(Square& square, Piece& piece) const;
	void enPassant(Square& square, Piece& piece) const;
	void setPlayers(Player& whitePlayer, Player& blackPlayer);
	void setBoard(Board& board);
	void onPawnPromotionTriggered(Square& square, Piece& piece);
};

