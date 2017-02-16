#include <precompiled.h>
#include <Utilities/Math/LuaMathHelper.h>

namespace math
{

	void LuaMathHelper::RegisterToLua(luabridge::lua_State* L)
	{
		getGlobalNamespace(L)
			//Vector2
			.beginClass<vec2<>>("vec2")
				.addConstructor<void(*)(float, float)>()
				.addData("x", &vec2<>::x)
				.addData("y", &vec2<>::y)
				.addFunction("length", &vec2<>::length)
				.addFunction("squaredLength", &vec2<>::squaredLength)
				.addFunction("normalize", &vec2<>::normalize)
			.endClass()
			//Vector3
			.beginClass<vec3<>>("vec3")
			.addConstructor<void(*)(float, float, float)>()
			.addData("x", &vec3<>::x)
			.addData("y", &vec3<>::y)
			.addData("z", &vec3<>::z)
			.addFunction("length", &vec3<>::length)
			.addFunction("squaredLength", &vec3<>::squaredLength)
			.addFunction("normalize", &vec3<>::normalize)
			.endClass();
	}

}