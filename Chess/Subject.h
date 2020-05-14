#pragma once
#include <vector>
#include <SFML/Window.hpp>

class IObserver;

class Subject
{
private:
	std::vector<IObserver*> m_Observers;

public:
	void attach(IObserver& observer);
	void notify(const sf::Event& event, const sf::Vector2i& mousePosition) const;
};

