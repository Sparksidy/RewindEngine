#include <precompiled.h>

#include <Engine/Engine.h>
#include <Systems/Scripting/ScriptLoader/ScriptLoader.h>

#include "Systems\Audio\AudioManager.h"

using namespace luabridge;

int main(int argc, char** argv)
{
	Engine daEngine;

#pragma region Initialize_Lua_libs

	//Initialize Lua & Lua Bridge
	luabridge::lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	ScriptLoader::s_mainLuaState = L;

	//Run useful enums Lua file...
	int err = luaL_dofile(L, "Resources/Lua_Scripts/Enums.lua");
#pragma endregion

	daEngine.AllocateSystems();

	Engine::RegisterToLua(L);



	//perform full gc
	lua_gc(L, LUA_GCCOLLECT, 0);
	lua_gc(L, LUA_GCCOLLECT, 0);

	if (daEngine.Initialize())
	{
		daEngine.Run();
	}

	daEngine.Unload();

	daEngine.DeallocateSystems();

#pragma region Unload_Lua_libs
	//perform full gc
	lua_gc(L, LUA_GCCOLLECT, 0);
	lua_gc(L, LUA_GCCOLLECT, 0);

	lua_close(L);
#pragma endregion

	return 0;
}