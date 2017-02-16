#include <precompiled.h>
#include "ScriptingManager.h"

#include <Systems/Core/GameObjectManager.h>
#include <Engine/Engine.h>
#include "../Components/LuaScriptComponent.h"
#include "../ScriptLoader/ScriptLoader.h"

ScriptingManager::ScriptingManager()
{

}

ScriptingManager::~ScriptingManager()
{

}

bool ScriptingManager::Initialize()
{
	ScriptLoader::LoadScript("BaseScript.lua");
	return m_isInitialized = true;
}

void ScriptingManager::Update(float dt)
{
	static GameObjectManager * gameObjectManager = 
		dynamic_cast<GameObjectManager*>(Engine::GetEngineSingleton().GetSystem("GameObjectManager"));
	LuaScriptComponent* script;
	for (auto gameObject : gameObjectManager->m_gameObjects)
	{
		if (!gameObject->GetActive())
			continue;

		if( script = (LuaScriptComponent*)gameObject->GetComponent(LUA_SCRIPT_COMPONENT))
			script->Update(dt);
	}
}

void ScriptingManager::Unload()
{
}

void ScriptingManager::ReceiveMessage(Message* msg)
{
}

string ScriptingManager::GetName() const
{
	return "ScriptingSystem";
}