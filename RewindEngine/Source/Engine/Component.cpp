#include <precompiled.h>
#include <Engine\Component.h>
#include <Engine\GameObject.h>

#pragma region "Constructors"
Component::Component(unsigned int Type)
{

	m_pOwner = nullptr;
	m_ComponentType = Type;
}

#pragma endregion "Constructors"

#pragma region "Getters"

unsigned int Component::GetComponentType()
{
	return m_ComponentType;
}

void Component::RegisterToLua(luabridge::lua_State* L)
{
	getGlobalNamespace(L);
}

#pragma endregion