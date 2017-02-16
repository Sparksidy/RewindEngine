#include <precompiled.h>
#include <Systems\Core\GameObjectManager.h>
#include <Engine\GameObject.h>
#include <Engine\Component.h>

#include <string>
#include <fstream>
#include <streambuf>

#include <rapidjson\document.h>
#include <Engine\Engine.h>

#pragma region "Constructors/Destructors"
GameObjectManager::GameObjectManager()
{

}
GameObjectManager::~GameObjectManager()
{

}
#pragma endregion

void GameObjectManager::LoadObject(JSONObject const & object)
{

	GameObject * gameObject = new GameObject();
	
	auto & componentsMember = object.FindMember("Components");
	if (componentsMember != object.MemberEnd())
	{
		auto componentsObject = componentsMember->value.GetObject();
		for (auto componentsIterator = componentsObject.MemberBegin(); componentsIterator != componentsObject.MemberEnd(); ++componentsIterator)
		{
			char const * componentType = componentsIterator->name.GetString();
			auto componentObject = componentsIterator->value.GetObject();

			if (strcmp(componentType, "Transform") == 0)
			{
				gameObject->AddComponent(TRANSFORM_COMPONENT, componentObject);
			}
			else if (strcmp(componentType, "Sprite") == 0)
			{
				gameObject->AddComponent(SPRITE_COMPONENT, componentObject);
			}
			else if (strcmp(componentType, "AnimatedSprite") == 0)
			{
				gameObject->AddComponent(ANIMATED_SPRITE_COMPONENT, componentObject);
			}

			else if (strcmp(componentType, "LuaScript") == 0)
			{
				gameObject->AddComponent(LUA_SCRIPT_COMPONENT, componentObject);
			}
			else if (strcmp(componentType, "Rigidbody") == 0)
			{
				gameObject->AddComponent(RIGIDBODY_COMPONENT, componentObject);
			}
		}
	}

	m_gameObjects.push_back(gameObject);
}

#pragma region "ISystem Methods"

bool GameObjectManager::Initialize()
{
	return true;
}

void GameObjectManager::Update(float dt)
{

}

void GameObjectManager::Unload()
{
	for (auto gameObject : m_gameObjects)
		delete gameObject;

	m_gameObjects.clear();
}

void GameObjectManager::ReceiveMessage(Message * msg)
{

}

string GameObjectManager::GetName() const
{
	return "GameObjectManager";
}

#pragma endregion

#pragma region "Constructors/Destructors"
Archetype::Archetype() 
{
	
}

Archetype::~Archetype()
{
	
}
#pragma endregion


#pragma region "public methods"
//Loads the file from the system
void  Archetype::CreateArchetype(ARCHETYPENAME name, JSONObject const & object)
{
	
		//Create the game object
		GameObject* gameObject = new GameObject();

		auto & componentsMember = object.FindMember("Components");
		if (componentsMember != object.MemberEnd())
		{
			auto componentsObject = componentsMember->value.GetObject();
			for (auto componentsIterator = componentsObject.MemberBegin(); componentsIterator != componentsObject.MemberEnd(); ++componentsIterator)
			{
				char const * componentType = componentsIterator->name.GetString();
				auto componentObject = componentsIterator->value.GetObject();

				if (strcmp(componentType, "Transform") == 0)
				{
					gameObject->AddComponent(TRANSFORM_COMPONENT, componentObject);
				}
				else if (strcmp(componentType, "Sprite") == 0)
				{
					gameObject->AddComponent(SPRITE_COMPONENT, componentObject);
				}
				else if (strcmp(componentType, "AnimatedSprite") == 0)
				{
					gameObject->AddComponent(ANIMATED_SPRITE_COMPONENT, componentObject);
				}

				else if (strcmp(componentType, "LuaScript") == 0)
				{
					gameObject->AddComponent(LUA_SCRIPT_COMPONENT, componentObject);
				}
			}
		}

		//Get the gameObjectManager
		static GameObjectManager* gameObjectManager = dynamic_cast<GameObjectManager* >(Engine::GetEngineSingleton().GetSystem("GameObjectManager"));

		//Insert the created archetype in the map
		gameObjectManager->m_archetypesmap.insert(std::pair<ARCHETYPENAME, GameObject*>(name, gameObject));
		
}
#pragma endregion

#pragma region "Private methods"
GameObject* Archetype::GetArchetype(ARCHETYPENAME name)
{
	//Insert the created archetype in the map
	static GameObjectManager* gameObjectManager = dynamic_cast<GameObjectManager* >(Engine::GetEngineSingleton().GetSystem("GameObjectManager"));

	std::map<ARCHETYPENAME, GameObject*>::const_iterator iter;

	iter = gameObjectManager->m_archetypesmap.find(name);
	if (iter != gameObjectManager->m_archetypesmap.end())
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}
}

#pragma endregion