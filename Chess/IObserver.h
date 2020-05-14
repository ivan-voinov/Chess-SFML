#pragma once
#include <SFML/Window.hpp>

class InputEvent;

class IObserver
{
public:
	virtual void update(const InputEvent& event) = 0;
};

