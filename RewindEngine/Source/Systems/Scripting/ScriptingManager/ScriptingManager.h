/*

File: ScriptingManager.h
Author: Esteban Maldonado
Date Created: January 23, 2017

Modified by(optional):
Date Modified(optional):

Purpose(optional):

*/
#pragma once

#include <Systems/Core/ISystem.h>

//Forward declaration
namespace luabridge
{
	struct lua_State;
}

class ScriptingManager : public ISystem
{
public:
	ScriptingManager();
	virtual ~ScriptingManager() override;

	//ISystem inherited methods...
	virtual bool Initialize() override;
	virtual void Update(float dt) override;
	virtual void Unload() override;
	virtual void ReceiveMessage(Message* msg) override;
	virtual string GetName() const override;

protected:
	luabridge::lua_State* m_luaState;
};