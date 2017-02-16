#include <precompiled.h>
#include <Engine\Scene.h>

#pragma region "Contsructor/Destructor"

Scene::Scene()
{
	

}

Scene::~Scene()
{

}

#pragma endregion

#pragma region "Public methods"

void Scene::AddLayer(Layer* layer)
{
	LayerContainer.push_back(layer);
}

void Scene::RemoveFront()
{
	LayerContainer.pop_back();
}

std::vector<Layer*>::const_iterator Scene::GetBeginIterator() const
{
	return LayerContainer.begin();
}
std::vector<Layer*>::const_iterator Scene::GetEndIterator() const
{
	return LayerContainer.end();
}

#pragma endregion