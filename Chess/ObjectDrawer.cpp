#include "pch.h"
#include "ObjectDrawer.h"


ObjectDrawer::ObjectDrawer()
{
}

void ObjectDrawer::addNewObject(sf::Drawable* objectToAdd)
{
	m_DrawableObjects.push_back(objectToAdd);
}

void ObjectDrawer::drawObjects(sf::RenderWindow& window)
{
	for (auto& object : m_DrawableObjects)
	{
		window.draw(*object);
	}
}

void ObjectDrawer::removeObject(sf::Drawable* objectToDelete)
{
	std::vector<sf::Drawable*>::iterator it;
	it = m_DrawableObjects.begin();
	while (it != m_DrawableObjects.end())
	{
		if (*it == objectToDelete)
			m_DrawableObjects.erase(it);
		++it;
	}
}

void ObjectDrawer::cleanUpDestroyedObjects()
{
	for (auto& object : m_DrawableObjects)
	{
		if (object == NULL)
			removeObject(object);
	}
}


ObjectDrawer::~ObjectDrawer()
{
}
