/*
	FILE:			Scene.h
	AUTHOR:			Siddharth Gupta
	DATE CREATED:	1/15/17
*/

#pragma once

#include <vector>

class Layer;

class Scene
{

public:

	//Constructors & destructors
	Scene();
	~Scene();

	//public methods
	void AddLayer(Layer* layer);
	void RemoveFront();
	std::vector<Layer*>::const_iterator GetBeginIterator() const;
	std::vector<Layer*>::const_iterator GetEndIterator() const;

private:
	std::vector<Layer* > LayerContainer;
};
