#include "precompiled.h"
#include "TransformComponent.h"

#pragma region "Constructors/Destructor"

TransformComponent::TransformComponent() : Component(TRANSFORM_COMPONENT)
{
}

TransformComponent::~TransformComponent()
{
}

#pragma endregion

#pragma region "Component Methods"

void TransformComponent::Serialize(JSONObject const & object)
{
	auto it = object.FindMember("Translation");
	if (it != object.MemberEnd())
	{
		auto translationArray = it->value.GetArray();
		m_translation.x = translationArray[0].GetFloat();
		m_translation.y = translationArray[1].GetFloat();
	}

	it = object.FindMember("Rotation");
	if (it != object.MemberEnd())
		m_rotation = it->value.GetFloat();

	it = object.FindMember("Scale");
	if (it != object.MemberEnd())
	{
		auto scaleArray = it->value.GetArray();
		m_scale.x = scaleArray[0].GetFloat();
		m_scale.y = scaleArray[1].GetFloat();
	}
}

math::vec2<> TransformComponent::GetTranslation() const
{
	return m_translation;
}

void TransformComponent::SetTranslation(math::vec2<> t)
{
	m_translation = t;
}

float TransformComponent::GetRotation() const
{
	return m_rotation;
}

void TransformComponent::SetRotation(float rot)
{
	m_rotation = rot;
}

math::vec2<> TransformComponent::GetScale() const
{
	return m_scale;
}

void TransformComponent::SetScale(math::vec2<> t)
{
	m_scale = t;
}

#pragma endregion



void TransformComponent::RegisterToLua(luabridge::lua_State* L)
{
	getGlobalNamespace(L)
		//.deriveClass<TransformComponent, Component>("TransformComponent")
		.beginClass<TransformComponent>("TransformComponent")
			.addConstructor<void(*) (void)>()
			.addFunction("GetComponentType", &TransformComponent::GetComponentType)
			.addProperty("translation", &TransformComponent::GetTranslation, &TransformComponent::SetTranslation)
			.addProperty("rotation", &TransformComponent::GetRotation, &TransformComponent::SetRotation)
			.addProperty("scale", &TransformComponent::GetScale, &TransformComponent::SetScale)
		.endClass();
}