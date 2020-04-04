#include "pch.h"
#include "ChessLogic.h"
#include "GameManager.h"


ChessLogic::ChessLogic() :
	m_WhitePlayer(sf::Color::White),
	m_BlackPlayer(sf::Color::Black)
{
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
}

void ChessLogic::onClick(sf::RenderWindow& window)
{
	if (m_WhitePlayer.isPlayerTurn())
	{
		m_WhitePlayer.processTurn(m_Board, window);
	}
	else if (m_BlackPlayer.isPlayerTurn())
	{
		m_BlackPlayer.processTurn(m_Board, window);
	}
}

ChessLogic::~ChessLogic()
{
}
