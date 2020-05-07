#pragma once
#include <SFML/Graphics.hpp>
#include "ITriggered.h"
#include "GameObject.h"
#include "IOpaque.h"
#include "ResourceManager.h"

class Square;
class MoveValidator;
class ILineValidator;

class Piece : public GameObject, public ITriggered, public IOpaque
{
protected:
	int m_SquareId;
	sf::Sprite m_PieceSprite;
	sf::Color m_Color;
	std::vector<int> m_LegalSquaresIds;
	MoveValidator* m_MoveValidator = nullptr;
	ILineValidator* m_LineValidator = nullptr;

	void setSpriteTexture(const sf::Texture& texture);
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
	void attachMoveValidator(MoveValidator* moveValidator);
	void setSquare(const Square& square);
	void attachLineValidator(ILineValidator* lineValidator);
	virtual void move(Square& square, bool isMockingMove);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void onSuccessfulMove() = 0;
	virtual bool controlsSquare(const Square& square) const = 0;
	virtual bool isLegalMove(Square & square);
	bool isTriggered(const sf::Vector2i& mousePosition) const override;
	void setOpacity(sf::Uint8 opacity) override;
	virtual ~Piece();
};

