/*

File: LuaScriptComponent.h
Author: Esteban Enrique Maldonado Cabán
Date Created: February 1, 2017

Modified by(optional):
Date Modified(optional):

Purpose(optional):


*/
#pragma once

#include <Engine/Component.h>

//Forward declarations...
namespace luabridge
{
	struct lua_State;
	class LuaRef;
}

class LuaScriptComponent : public Component
{
public:
	LuaScriptComponent();
	virtual ~LuaScriptComponent();

	virtual void Update(float dt);


	virtual void Serialize(JSONObject const & object) override;

private:
	/* This is a reference to an INSTANCE of a lua table that we can ask to
	* do stuff. It's a pointer as otherwise the GameObject constructor would
	* need a lua_State to init this LuaRef*/
	luabridge::LuaRef *m_luaClass;
	std::string m_fileName;

	luabridge::LuaRef *m_luaGORef;
};