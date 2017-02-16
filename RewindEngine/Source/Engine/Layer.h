/*
File: Layer.h
Author: David Westen
Date Created: 1/18/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/

#pragma once
#include <vector>

class GameObject;

class Layer
{
public:

	//constructors/destructor
	Layer();
	~Layer();

	//getters
	typename std::vector<GameObject const *>::const_iterator GetBegin() const;
	typename std::vector<GameObject const *>::const_iterator GetEnd() const;

	//public methods
	void AddGameObject(GameObject const & gameObject);
	void RemoveGameObject(GameObject const & gameObject);
	void SortGameObjects();

private:
	
	std::vector<GameObject const *> m_gameObjects;

};

