#include "pch.h"
#include "GameStateController.h"
#include "GameManager.h"
#include "Player.h"
#include "Button.h"
#include "ChessLogic.h"
#include <iostream>

GameStateController::GameStateController()
{
	const sf::SoundBuffer* checkMateSound = GameManager::getInstance().getAudioManager().getResource("checkMate");
	if (checkMateSound)
		m_CheckmateSound.setBuffer(*checkMateSound);
}

GameStateController::GameState GameStateController::getGameState(const Player& currentPlayer) const
{
	return m_GameState;
}

void GameStateController::updateGameState(const Player& currentPlayer, ChessLogic& chess)
{
	bool noLegalMoves = currentPlayer.hasNoLegalMoves();
	if (noLegalMoves && currentPlayer.isChecked())
	{
		m_GameState = GameState::CHECKMATE;
		m_GameOver = true;
		onGameOver(chess);
	}
	else if (noLegalMoves)
	{
		m_GameState = GameState::STALEMATE;
		m_GameOver = true;
		onGameOver(chess);
	}
	else
	{
		m_GameState = GameState::IN_PLAY;
		m_GameOver = false;
	}
}

void GameStateController::onGameOver(ChessLogic& chess)
{
	const sf::Vector2u& windowDimensions = GameManager::getInstance().getWindowDimensions();
	Button restart("restartButton", "buttonFont");
	restart.setOnClickAction([this, &restart, &chess]() {
		chess.restartGame();
		m_GameOver = false;
	});
	restart.setPosition(sf::Vector2f(windowDimensions.x / 2, windowDimensions.y / 2));
	restart.setSize(sf::Vector2f(windowDimensions.x / 2, windowDimensions.y / 5));
	restart.setTextSize(200);
	restart.setTextString("Restart");
	restart.setTextColor(sf::Color::White);

	m_RestartButtonId = restart.getId();
	GameManager::getInstance().addGameObject(std::make_unique<Button>(std::move(restart)));
	switch (m_GameState)
	{
	case GameState::CHECKMATE:
		m_CheckmateSound.play();
		std::cout << "CHECKMATE";
		break;

	case GameState::STALEMATE:
		std::cout << "STALEMATE";
		break;

	case GameState::DRAW:
		std::cout << "DRAW";
		break;
	}
}

void GameStateController::onClick(const sf::Vector2i& mousePosition)
{
	Button* restart = GameManager::getInstance().getGameObject<Button>(m_RestartButtonId);
	if (restart->isTriggered(mousePosition))
	{
		restart->executeAction();
		restart->destroy();
	}
}

bool GameStateController::gameIsOver()
{
	return m_GameOver;
}