#pragma once
#include <SFML/Audio.hpp>

class Player;
class ChessLogic;

class GameStateController
{
public:
	enum class GameState
	{
		CHECKMATE,
		STALEMATE,
		DRAW,
		IN_PLAY
	};

private:
	bool m_GameOver = false;
	GameState m_GameState = GameState::IN_PLAY;
	sf::Sound m_CheckmateSound;
	sf::Sound m_StalemateSound;
	int m_RestartButtonId = -1;

public:
	GameStateController();
	GameState getGameState(const Player& currentPlayer) const;
	void updateGameState(const Player& currentPlayer, ChessLogic& chess);
	void onGameOver(ChessLogic& chess);
	void onClick(const sf::Vector2i& mousePosition) const;
	void onMouseMoved(const sf::Vector2i& mousePosition) const;
	bool gameIsOver();
};

