#pragma once
#include "SFML/Graphics.hpp"

class Board;
class Square;
class Piece;
class King;
class MoveValidator;

class Player
{
private:
	Player* m_Opponent = nullptr;
	int m_FocusedPieceId = -1;
	int m_LastMovedPieceId = -1;
	int m_KingId = -1;
	std::vector<int> m_PiecesIds;
	std::vector<int> m_PawnPromotionPiecesIds;
	bool m_MoveIsPaused = false;
	bool m_IsPlayerTurn;
	sf::Color m_Color;
	std::vector<std::reference_wrapper<Square>> getSquaresForDisplayedPieces(Square& square, const Board& board) const;
	void displayPiecesToChoose(const std::vector<std::reference_wrapper<Square>>& squaresForDisplayedPieces);
	Piece* getTriggeredPromotedPiece(const sf::Vector2i& mousePosition) const;

public:
	Player(const sf::Color& playerColor);
	void onPawnPromotionTriggered(Square& square, Board& board);
	void onPawnPromotionCompleted(Board& board);
	void computeLegalMoves(const Board& board);
	void addPiece(int pieceId);
	Piece* getTriggeredPiece(const sf::Vector2i& mousePosition) const;
	Piece* findPiece(const Square& square) const;
	King* getKing() const;
	void attachOpponent(Player& opponent);
	void setKing(int kingId);
	void removePiece(int capturedPieceId);
	bool isChecked(const Board& board) const;
	bool hasNoLegalMoves() const;
	bool controlsSquare(Square& square, const Board& board);
	void resizePieces(double squareSize);
	bool pieceIsChosen() const;
	bool isPlayerTurn() const;
	void makeMove(Square& square, Board& board, Piece& focusedPiece);
	void onSuccessfulMove(Board& board, Square& square, Piece& piece);
	void onFailedMove(Square& square);
	bool processTurn(Board& board, sf::RenderWindow& window);
	void choosePiece(const Board& board, Piece& triggeredPiece);
	void switchTurn();
	void resetMoveState(Square& square);
	void highlightSquare(Square& square);
	void setMoveValidator(MoveValidator& moveValidator);
	void updateCheckedState(Board& board, Square& startSquare, Piece& piece) const;
	const sf::Color& getColor() const;
	~Player();
};

