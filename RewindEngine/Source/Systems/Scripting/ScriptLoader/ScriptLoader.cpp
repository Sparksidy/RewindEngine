#include <precompiled.h>
#include "ScriptLoader.h"

luabridge::LuaRef* ScriptLoader::GetLuaClassRef(string name)
{
	ScriptMap::iterator it = s_loadedScripts.find(name);
	if(it == s_loadedScripts.end())
		return nullptr;

	return it->second;
}

void ScriptLoader::ClearAllScripts()
{
	for(ScriptMap::iterator it = s_loadedScripts.begin(); 
		it != s_loadedScripts.end(); ++it)
	{
		SafeDelete(it->second);
	}

	s_loadedScripts.clear();
}

void ScriptLoader::ReloadAllScripts()
{
}

luabridge::LuaRef ScriptLoader::LoadScript(string name, bool reload)
{
	if(!reload)
	{
		//determine if the script has already been loaded
		ScriptMap::iterator it = s_loadedScripts.find(name);
		if (it != s_loadedScripts.end())
		{
			return *s_loadedScripts[name];
		}
	}

	std::cout << "Loading script " << s_scriptFolder + name << std::endl;
	int error = luaL_dofile(s_mainLuaState, (s_scriptFolder + name).c_str());
	if (error)
	{
		HandleError();
	}
	else 
	{
		luabridge::LuaRef registerfunc = getGlobal(s_mainLuaState, "register_script");

		if (registerfunc.isFunction()) 
		{
			luabridge::LuaRef classdef = registerfunc();
			
			if (classdef.isTable())
			{
				s_loadedScripts[name] = new luabridge::LuaRef(classdef);
				return *(s_loadedScripts[name]);
			}
		}
		else 
		{
			std::cout << "Error loading script " << name << " no register_script function" << std::endl;
		}
	}

	return luabridge::LuaRef(s_mainLuaState);
}

void ScriptLoader::HandleError()
{
	std::string str = lua_tostring(s_mainLuaState, lua_gettop(s_mainLuaState));
	lua_pop(s_mainLuaState, 1);

	luabridge::lua_Debug entry;
	int depth = 0;

	int v;
	while ((v = lua_getstack(s_mainLuaState, depth, &entry)) != 0)
	{
		int status = lua_getinfo(s_mainLuaState, "Sln", &entry);
		assert(status);

		std::cout << entry.short_src << "(" << entry.currentline << ") " << (entry.name ? entry.name : "?") << std::endl;
		depth++;
	}
	std::cout << "Lua Error: " << str.c_str() << std::endl;
}

luabridge::lua_State* ScriptLoader::s_mainLuaState = nullptr;
const string ScriptLoader::s_scriptFolder = "Resources/Lua_Scripts/";
ScriptMap ScriptLoader::s_loadedScripts = ScriptMap();

