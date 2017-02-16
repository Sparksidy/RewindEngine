#pragma once

//Forward declaration
namespace luabridge
{
	struct lua_State;
}

namespace math
{
	class LuaMathHelper
	{
	public:
		/*For some reason it complained if I did not have this function
		outside of a class...meh*/
		static void RegisterToLua(luabridge::lua_State* L);
	};
}