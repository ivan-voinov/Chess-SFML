#pragma once
#include <vector>
#include <SFML/Window.hpp>

class IObserver;
class InputEvent;

class Subject
{
private:
	std::vector<IObserver*> m_Observers;

public:
	void attach(IObserver& observer);
	void notify(const InputEvent& event) const;
};

