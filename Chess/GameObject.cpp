#include "pch.h"
#include "GameObject.h"
#include "GameManager.h"

int GameObject::s_NextId = 1;

GameObject::GameObject()
{
	m_Id = generateUniqueId();
}

bool operator== (const GameObject& g1, const GameObject& g2)
{
	return (g1.m_Id == g2.m_Id);
}

bool operator!= (const GameObject& g1, const GameObject& g2)
{
	return !(g1 == g2);
}

bool operator== (const GameObject& g1, int id)
{
	return (g1.m_Id == id);
}

bool operator!= (const GameObject& g1, int id)
{
	return !(g1 == id);
}

int GameObject::generateUniqueId()
{
	return s_NextId++;
}

int GameObject::getId() const
{
	return m_Id;
}

void GameObject::destroy()
{
	m_IsDestroyed = true;
}

bool GameObject::isDestroyed() const
{
	return m_IsDestroyed;
}

GameObject::~GameObject()
{
}
