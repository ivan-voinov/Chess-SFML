#include "pch.h"
#include "ChessLogic.h"


ChessLogic::ChessLogic(const sf::Vector2u& windowDimensions) :
	m_WhitePlayer(sf::Color::White),
	m_BlackPlayer(sf::Color::Black),
	m_WindowDimensions(windowDimensions)
{
}


void ChessLogic::initializeGame()
{
	//Load the board and the pieces
	m_Board.buildBoard(m_WindowDimensions);
	m_Board.assignPiecesToPlayers(m_WhitePlayer, m_BlackPlayer);

	//Give the players a pointer to each other
	m_WhitePlayer.attachOpponent(m_BlackPlayer);
	m_BlackPlayer.attachOpponent(m_WhitePlayer);

	//Resize the pieces according to the size of square
	m_WhitePlayer.resizePieces(m_Board.getSquareSize());
	m_BlackPlayer.resizePieces(m_Board.getSquareSize());

	m_WhitePlayer.attachMoveValidatorToPieces();
	m_BlackPlayer.attachMoveValidatorToPieces();

	m_WhitePlayer.attachSquareGetter(&m_Board);
	m_BlackPlayer.attachSquareGetter(&m_Board);

	m_WhitePlayer.computeLegalMoves();
}

void ChessLogic::onClick(const sf::Vector2i& mousePosition)
{
	if (!m_GameStateController.gameIsOver())
	{
		if (m_WhitePlayer.isPlayerTurn() && m_WhitePlayer.processTurn(mousePosition))
			m_GameStateController.updateGameState(m_BlackPlayer, *this);

		else if (m_BlackPlayer.isPlayerTurn() && m_BlackPlayer.processTurn(mousePosition))
			m_GameStateController.updateGameState(m_WhitePlayer, *this);
	}
	else
	{
		m_GameStateController.onClick(mousePosition);
	}
	//TODO: ELSE transition to another screen / restart the game
	//TODO: DRAW without stalemate
}

void ChessLogic::onMouseMoved(const sf::Vector2i& mousePosition)
{
	if (m_WhitePlayer.isPlayerTurn())
		m_WhitePlayer.dragFocusedPiece(mousePosition);
	else
		m_BlackPlayer.dragFocusedPiece(mousePosition);
}

void ChessLogic::update(const sf::Event& event, const sf::Vector2i& mousePosition)
{
	if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
		onClick(mousePosition);
	if (event.type == sf::Event::MouseMoved)
		onMouseMoved(mousePosition);
}

void ChessLogic::destroyGame()
{
	m_Board.destroyBoard();
	m_WhitePlayer.destroyPieces();
	m_BlackPlayer.destroyPieces();
}

void ChessLogic::restartGame()
{
	destroyGame();
	initializeGame();
}

ChessLogic::~ChessLogic()
{
}
