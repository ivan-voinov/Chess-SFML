#include "pch.h"
#include "ChessGame.h"

ChessGame::ChessGame(sf::VideoMode mode, const std::string &title, sf::Uint32 style)
{
	m_Window.create(mode, title, style);
	m_Board.loadBoard(m_Window, m_ObjectDrawer);
}

void ChessGame::readInput()
{
	while (m_Window.pollEvent(m_Event))
	{
		switch (m_Event.type)
		{
			case sf::Event::Closed:
			{
				m_Window.close();
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				m_Board.readInput(sf::Mouse::getPosition(m_Window));
			}
		}
	}
}

void ChessGame::update()
{

}

void ChessGame::draw()
{
	m_Window.clear();
	m_ObjectDrawer.cleanUpDestroyedObjects();
	m_ObjectDrawer.drawObjects(m_Window);
	m_Window.display();
}

void ChessGame::runGame()
{
	while (m_Window.isOpen())
	{
		readInput();
		update();
		draw();
	}
}

ChessGame& ChessGame::getInstance(sf::VideoMode mode, const std::string &title, sf::Uint32 style)
{
	static ChessGame chessGame(mode, title, style);
	return chessGame;
}

ChessGame::~ChessGame()
{
}
