#pragma once
#include <SFML/Graphics.hpp>
#include "ITriggered.h"
#include "GameObject.h"
#include "MoveValidator.h"

class Square;
class Board;

class Piece : public GameObject, public ITriggered
{
protected:
	int m_SquareId;
	sf::Texture m_PieceTexture;
	sf::Sprite m_PieceSprite;
	sf::Color m_Color;
	std::vector<int> m_LegalSquaresIds;
	MoveValidator* m_MoveValidator = nullptr;

	void loadTexture(const std::string& piecePath);
	void setOriginAndPosition(const sf::Vector2f& position);

public:
	Piece(const sf::Vector2f& position, const sf::Color& color);
	Piece(const sf::Vector2f& position, int squareId, const sf::Color& color);
	const sf::Color& getColor() const;
	Square* getSquare() const;
	void resize(const double squareSize);
	void updateSquareState(Square& square, bool isMockingMove);
	void clearLegalSquares();
	void addLegalSquare(int squareId);
	void displayLegalMoves() const;
	void hideLegalMoves() const;
	bool findLegalSquare(const Square& square) const;
	bool hasNoLegalSquares() const;
	void setMoveValidator(MoveValidator& moveValidator);
	virtual void move(Square& square, bool isMockingMove);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void onSuccessfulMove() = 0;
	virtual bool controlsSquare(const Square& square, const Board& board) const = 0;
	virtual bool isLegalMove(Square & square, const Board& board);
	virtual bool isTriggered(const sf::Vector2i& mousePosition) const override;
	~Piece();
};

