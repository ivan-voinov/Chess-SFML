#pragma once
#include "Player.h"
#include "Board.h"
#include "MoveHistory.h"
#include "MoveValidator.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourceManager.h"

class ChessLogic
{
private:
	Board m_Board;
	Player m_WhitePlayer;
	Player m_BlackPlayer;
	MoveHistory m_MoveHistory;
	MoveValidator m_MoveValidator;
	ResourceManager<sf::SoundBuffer> m_AudioManager;
	sf::Sound m_CheckmateSound;
	sf::Sound m_StalemateSound;
	bool m_GameOver = false;

	enum class GameState
	{
		CHECKMATE,
		STALEMATE,
		DRAW,
		IN_PLAY
	};

public:
	ChessLogic();
	GameState getGameState(const Player& currentPlayer) const;
	void initializeGame(const sf::RenderWindow& window);
	void onClick(sf::RenderWindow& window);
	void gameOver(const GameState& gameOutcome);
	~ChessLogic();
};

