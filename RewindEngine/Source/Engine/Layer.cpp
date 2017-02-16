/*
File: Layer.cpp
Author: David Westen
Date Created: 1/18/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/
#include <precompiled.h>
#include <Engine\Layer.h>

#pragma region "Priority Queue Predicate"



#pragma endregion

#pragma region "Constructors/Destructor"

Layer::Layer() : m_gameObjects(100)
{

}


Layer::~Layer()
{
}

#pragma endregion

#pragma region "Getters"

typename std::vector<GameObject const *>::const_iterator Layer::GetBegin() const
{
	return m_gameObjects.cbegin();
}

typename std::vector<GameObject const *>::const_iterator Layer::GetEnd() const
{
	return m_gameObjects.cend();
}

#pragma endregion

#pragma region "Public Methods"

void Layer::AddGameObject(GameObject const & gameObject)
{
	
}

void Layer::RemoveGameObject(GameObject const & gameObject)
{

}

void Layer::SortGameObjects()
{
	
}

#pragma endregion