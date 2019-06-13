#pragma once
#include <SFML/Graphics.hpp>


class ObjectDrawer
{
private:
	sf::RenderWindow* m_Window;
	std::vector<sf::Drawable*> m_DrawableObjects;
public:
	ObjectDrawer();
	void addNewObject(sf::Drawable* object);
	void drawObjects(sf::RenderWindow& window);
	void removeObject(sf::Drawable* object);
	void cleanUpDestroyedObjects();
	~ObjectDrawer();
};

