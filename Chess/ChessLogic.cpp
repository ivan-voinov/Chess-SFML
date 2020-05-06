#include "pch.h"
#include "ChessLogic.h"
#include "AssetPaths.h"
#include "FileException.h"
#include <iostream>


ChessLogic::ChessLogic() :
	m_WhitePlayer(sf::Color::White),
	m_BlackPlayer(sf::Color::Black)
{
	m_CheckmateSound.setBuffer(m_AudioManager.getResource("checkMate"));
}

ChessLogic::GameState ChessLogic::getGameState(const Player& currentPlayer) const
{
	bool noLegalMoves = currentPlayer.hasNoLegalMoves();
	if (noLegalMoves && currentPlayer.isChecked(m_Board))
	{
		return GameState::CHECKMATE;
	}
	else if (noLegalMoves)
	{
		return GameState::STALEMATE;
	}
	else
		return GameState::IN_PLAY;
}

void ChessLogic::initializeGame(const sf::RenderWindow& window)
{
	//Load the board and the pieces
	m_Board.buildBoard(window);
	m_Board.assignPiecesToPlayers(m_WhitePlayer, m_BlackPlayer);

	//Give the players a pointer to each other
	m_WhitePlayer.attachOpponent(m_BlackPlayer);
	m_BlackPlayer.attachOpponent(m_WhitePlayer);

	//Resize the pieces according to the size of square
	m_WhitePlayer.resizePieces(m_Board.getSquareSize());
	m_BlackPlayer.resizePieces(m_Board.getSquareSize());

	m_MoveValidator.setPlayers(m_WhitePlayer, m_BlackPlayer);
	m_MoveValidator.setBoard(m_Board);
	m_WhitePlayer.setMoveValidator(m_MoveValidator);
	m_BlackPlayer.setMoveValidator(m_MoveValidator);

	m_WhitePlayer.computeLegalMoves(m_Board);
}

void ChessLogic::onClick(sf::RenderWindow& window)
{
	if (!m_GameOver)
	{
		if (m_WhitePlayer.isPlayerTurn() && m_WhitePlayer.processTurn(m_Board, window))
		{
			GameState gameState = std::move(getGameState(m_BlackPlayer));
			if (gameState != GameState::IN_PLAY)
				gameOver(gameState);
		}
		else if (m_BlackPlayer.isPlayerTurn() && m_BlackPlayer.processTurn(m_Board, window))
		{
			GameState gameState = std::move(getGameState(m_WhitePlayer));
			if (gameState != GameState::IN_PLAY)
				gameOver(gameState);
		}
	}
	//TODO: ELSE transition to another screen / restart the game
	//TODO: DRAW without stalemate
}

void ChessLogic::gameOver(const GameState& gameOutcome)
{
	switch (gameOutcome)
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
	m_GameOver = true;
}

ChessLogic::~ChessLogic()
{
}
