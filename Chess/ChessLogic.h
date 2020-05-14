#pragma once
#include "Player.h"
#include "Board.h"
#include "MoveHistory.h"
#include <SFML/Graphics.hpp>
#include "GameStateController.h"
#include "IObserver.h"

class ChessLogic : public IObserver
{
private:
	Board m_Board;
	Player m_WhitePlayer;
	Player m_BlackPlayer;
	MoveHistory m_MoveHistory;
	GameStateController m_GameStateController;
	const sf::Vector2u m_WindowDimensions;

public:
	ChessLogic(const sf::Vector2u& windowDimensions);
	void initializeGame();
	void onClick(const sf::Vector2i& mousePosition);
	void onMouseMoved(const sf::Vector2i& mousePosition);
	void update(const sf::Event& event, const sf::Vector2i& mousePosition) override;
	void destroyGame();
	void restartGame();
	~ChessLogic();
};

