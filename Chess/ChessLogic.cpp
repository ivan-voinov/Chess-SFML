#include "pch.h"
#include "ChessLogic.h"
#include "GameManager.h"


ChessLogic::ChessLogic(Board* board, Player* whitePlayer, Player* blackPlayer)
{
	m_Board = board;
	m_WhitePlayer = whitePlayer;
	m_BlackPlayer = blackPlayer;
}

void ChessLogic::onClick(sf::RenderWindow& window)
{
	if (m_WhitePlayer->isPlayerTurn())
	{
		m_WhitePlayer->processTurn(*m_BlackPlayer, *m_Board, window);
	}
	else if (m_BlackPlayer->isPlayerTurn())
	{
		m_BlackPlayer->processTurn(*m_WhitePlayer, *m_Board, window);
	}
}

ChessLogic::~ChessLogic()
{
}
