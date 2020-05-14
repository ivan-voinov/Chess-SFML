#include "pch.h"
#include "InputEvent.h"

InputEvent::InputEvent(const sf::Event& event, bool isDragged) : m_Event{event}, m_IsDragged{isDragged}
{
}