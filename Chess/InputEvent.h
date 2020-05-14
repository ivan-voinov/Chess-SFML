#pragma once
#include <SFML/Window.hpp>

class InputEvent
{
public:
	const sf::Event m_Event;
	bool m_IsDragged;

	InputEvent(const sf::Event& event, bool m_IsDragged = false);
};

