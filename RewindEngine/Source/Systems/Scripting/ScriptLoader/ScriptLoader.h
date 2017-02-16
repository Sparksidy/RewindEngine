#pragma once

#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;

//Forward declarations...
namespace luabridge {
	struct lua_State;
	class LuaRef;
}

//typedefs...
typedef unordered_map<string, luabridge::LuaRef*> ScriptMap;

class ScriptLoader
{
public:
		static luabridge::lua_State* s_mainLuaState;
		//Getters
		static luabridge::LuaRef* GetLuaClassRef(string name);

		//Setters
		static void ClearAllScripts();
		static void ReloadAllScripts();
		static luabridge::LuaRef LoadScript(string name, bool reload = false);

		static void HandleError();

private:
	ScriptLoader(){}
	~ScriptLoader(){}

	static const string s_scriptFolder;
	static ScriptMap s_loadedScripts;
};