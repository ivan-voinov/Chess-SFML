#pragma once
#include "SFML/Graphics.hpp"

class GameObject : public sf::Drawable
{
private:
	static int s_NextId;
	int m_Id;
	int generateUniqueId();
	bool m_IsDestroyed = false;

public:
	GameObject();
	friend bool operator== (const GameObject& g1, const GameObject& g2);
	friend bool operator!= (const GameObject& g1, const GameObject& g2);
	friend bool operator== (const GameObject& g1, int id);
	friend bool operator!= (const GameObject& g1, int id);
	bool isDestroyed() const;
	int getId() const;
	void add();
	void destroy();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	~GameObject();
};

