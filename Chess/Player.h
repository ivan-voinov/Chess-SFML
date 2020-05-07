#pragma once
#include "SFML/Graphics.hpp"
#include "IOpaque.h"
#include "MoveValidator.h"

class ISquareGetter;
class Square;
class Piece;
class King;
class Rook;
class Pawn;


class Player : public MoveValidator
{
private:
	ISquareGetter* m_SquareGetter = nullptr;
	Player* m_Opponent = nullptr;
	int m_FocusedPieceId = -1;
	int m_LastMovedPieceId = -1;
	int m_KingId = -1;
	std::vector<int> m_PiecesIds;
	std::vector<int> m_PawnPromotionPiecesIds;
	bool m_MoveIsPaused = false;
	bool m_IsPlayerTurn;
	sf::Color m_Color;

	std::vector<std::reference_wrapper<Square>> getSquaresForDisplayedPieces(Square& square) const;
	void displayPiecesToChoose(const std::vector<std::reference_wrapper<Square>>& squaresForDisplayedPieces);
	Piece* getTriggeredPromotedPiece(const sf::Vector2i& mousePosition) const;
	Rook* getCastleRook(const Square& square, const Piece& piece) const;
	Square* getCastleAttackedSquare(const Square& square, const Piece& piece) const;
	Pawn* getCapturedEnPassantPawn(const Square& square, const Piece& piece) const;

public:
	Player(const sf::Color& playerColor);
	void attachSquareGetter(ISquareGetter* squareGetter);
	void onPawnPromotionTriggered(Square& square, Piece& piece) override;
	void onPawnPromotionCompleted(Piece& promotedPiece);
	void computeLegalMoves();
	void addPiece(int pieceId);
	Piece* getTriggeredPiece(const sf::Vector2i& mousePosition) const;
	Piece* findPiece(const Square& square) const;
	King* getKing() const;
	void attachOpponent(Player& opponent);
	void setKing(int kingId);
	void removePiece(int capturedPieceId);
	bool isChecked() const;
	bool hasNoLegalMoves() const;
	bool controlsSquare(Square& square);
	void resizePieces(double squareSize);
	bool pieceIsChosen() const;
	bool isPlayerTurn() const;
	void makeMove(Square& square, Piece& focusedPiece);
	void onSuccessfulMove(Square& startSquare, Piece* piece);
	void onFailedMove(Square& square);
	bool processTurn(sf::RenderWindow& window);
	void choosePiece(Piece& triggeredPiece);
	void switchTurn();
	void resetMoveState(Square& square);
	void highlightSquare(Square& square);
	void attachMoveValidatorToPieces();
	void updateCheckedState(Square& startSquare, Piece& piece) const;
	const sf::Color& getColor() const;
	void setOpacity(sf::Uint8 opacity) const;
	bool isLegalMove(Square& square, Piece& piece) override;
	bool castleIsLegal(Square& square, Piece& piece) override;
	bool enPassantIsLegal(Square& square, Piece& piece) override;
	void castle(Square& square, Piece& piece) const override;
	void enPassant(Square& square, Piece& piece) const override;
	~Player();
};

