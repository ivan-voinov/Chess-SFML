#pragma once
#include <SFML/Graphics.hpp>
#include "ITriggered.h"
#include "GameObject.h"
#include "IObserver.h"
#include "ISubject.h"


class Square;
class Board;

class Piece : public GameObject, public ITriggered, public ISubject
{
protected:
	int m_SquareId;
	sf::Texture m_PieceTexture;
	sf::Sprite m_PieceSprite;
	sf::Color m_Color;
	std::vector<IObserver*> m_Observers;

public:
	Piece(const sf::Vector2f& position, const sf::Color& color);
	const sf::Color& getColor() const;
	void setSquare(int squareId);
	Square* getSquare() const;
	void move(Square& square);
	void resize(const double squareSize);
	void updateSquareState(Square& square);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void onSuccessfulMove() = 0;
	virtual bool controlsSquare(const Square& square, const Board& board) const = 0;
	virtual bool isLegalMove(Square & square, const Board& board);
	virtual bool isTriggered(const sf::Vector2i& mousePosition) const override;
	virtual void registerObserver(IObserver* observer) override;
	virtual void removeObserver(IObserver* observer) override;
	virtual void notifyObserver(const std::string& event, Square& square, const Board& board) const override;
	~Piece();
};

