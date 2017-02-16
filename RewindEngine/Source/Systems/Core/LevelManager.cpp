#include "precompiled.h"
#include "LevelManager.h"

#include <fstream>

#include <rapidjson\document.h>

#include <Engine\Engine.h>
#include <Systems\Core\GameObjectManager.h>
#include <Systems\Core\ResourceManager.h>

#pragma region "Constructors/Destructor"

LevelManager::LevelManager()
{
}


LevelManager::~LevelManager()
{
}

#pragma endregion

#pragma region "ISystem Methods"

bool LevelManager::Initialize()
{
	return true;
}

void LevelManager::Update(float dt)
{

}

void LevelManager::Unload()
{

}

void LevelManager::ReceiveMessage(Message * msg)
{

}

string LevelManager::GetName() const
{
	return "LevelManager";
}

#pragma endregion

#pragma region "Public Methods"

void LevelManager::LoadLevel(char const * levelPath)
{

	ResourceManager * resourceManager = dynamic_cast<ResourceManager*>(Engine::GetEngineSingleton().GetSystem("ResourceManager"));
	GameObjectManager * gameObjectManager = dynamic_cast<GameObjectManager*>(Engine::GetEngineSingleton().GetSystem("GameObjectManager"));
	
	std::ifstream levelFile(levelPath, std::ios::in | std::ios::binary);
	std::string levelData((std::istreambuf_iterator<char>(levelFile)),
		std::istreambuf_iterator<char>());

	rapidjson::Document document;
	document.Parse(levelData.c_str());

	auto & resourcesValue = document["Resources"];
	if (!resourcesValue.IsNull())
	{
		auto resourcesArray = resourcesValue.GetArray();
		for (auto resourceIterator = resourcesArray.Begin(); resourceIterator != resourcesArray.End(); resourceIterator++)
			resourceManager->LoadResource(resourceIterator->GetString());
	}

	auto & objectsValue = document["Objects"];
	if (!objectsValue.IsNull())
	{
		auto objectsArray = objectsValue.GetArray();
		for (auto objectsIterator = objectsArray.Begin(); objectsIterator != objectsArray.End(); objectsIterator++)
			gameObjectManager->LoadObject(objectsIterator->GetObject());
	}
}

#pragma endregion