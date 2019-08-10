#pragma once
#include "SFML/Graphics.hpp"

class GameObject : public sf::Drawable
{
public:
	GameObject();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	~GameObject();
};

