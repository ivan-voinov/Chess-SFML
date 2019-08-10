#pragma once
#include <SFML/Graphics.hpp>

class GameObject;

class Collection
{
public:
	Collection();
	virtual void removeGameObject(GameObject* gameObject) = 0;
	~Collection();
};

