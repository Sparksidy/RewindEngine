#include<precompiled.h>
#include "../ScriptLoader/ScriptLoader.h"
#include "LuaScriptComponent.h"

LuaScriptComponent::LuaScriptComponent() : 
	m_luaClass(nullptr), m_luaGORef(nullptr), Component(LUA_SCRIPT_COMPONENT)
{
}

LuaScriptComponent::~LuaScriptComponent()
{
	if (m_luaGORef && m_luaGORef->isTable()) {
		luabridge::LuaRef destructor = (*m_luaGORef)["delete"];
		if (destructor.isFunction()) {
			destructor();
		}
	}
	delete m_luaGORef;
}

void LuaScriptComponent::Update(float dt)
{
	if (m_luaGORef == nullptr || m_luaGORef->isNil())
		return;

	luabridge::LuaRef tickfunc = (*m_luaGORef)["tick"];

	if (tickfunc.isFunction()) {
		tickfunc((*m_luaGORef), (double)dt);
	}
	else {
		std::cout << m_fileName << " tick isn't a function: " << tickfunc.type() << std::endl;
	}
}

void LuaScriptComponent::Serialize(JSONObject const & object)
{
	auto it = object.FindMember("FileName");
	if (it != object.MemberEnd())
	{
		string fileName = it->value.GetString();
		ScriptLoader::LoadScript(fileName);
		m_luaClass = ScriptLoader::GetLuaClassRef(fileName);

		if (m_luaGORef == nullptr)
			m_luaGORef = new luabridge::LuaRef((*m_luaClass)(this->m_pOwner));
	}
}
