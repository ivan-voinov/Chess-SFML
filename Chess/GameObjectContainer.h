#pragma once
#include <SFML/Graphics.hpp>

class GameObject;

class GameObjectContainer
{
public:
	GameObjectContainer();
	virtual void removeGameObject(GameObject* gameObject) = 0;
	~GameObjectContainer();
};

