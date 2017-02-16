#include "precompiled.h"
#include "RigidbodyComponent.h"

#pragma region "Constructors/Destructor"

RigidbodyComponent::RigidbodyComponent() : Component(RIGIDBODY_COMPONENT)
{
	m_hasCollision = true;
	m_enableGravity = true;
	m_collider_coef.x = 1;
	m_collider_coef.y = 1;
}

RigidbodyComponent::~RigidbodyComponent()
{

}

#pragma endregion

#pragma region "Component Methods"

void RigidbodyComponent::Serialize(JSONObject const & object)
{
	auto it = object.FindMember("Acceleration");
	if (it != object.MemberEnd())
		m_acceleration = it->value.GetFloat();

	it = object.FindMember("Mass");
	if (it != object.MemberEnd())
		m_mass = it->value.GetFloat();

	it = object.FindMember("RotVelocity");
	if (it != object.MemberEnd())
		m_rvelocity = it->value.GetFloat();

	it = object.FindMember("Gravity");
	if (it != object.MemberEnd())
		m_enableGravity = it->value.GetBool();

	it = object.FindMember("Velocity");
	if (it != object.MemberEnd())
	{
		auto velocityArray = it->value.GetArray();
		m_velocity.x = velocityArray[0].GetFloat();
		m_velocity.y = velocityArray[1].GetFloat();
	}

	it = object.FindMember("ColliderSize");
	if (it != object.MemberEnd())
	{
		auto colliderArray = it->value.GetArray();
		m_collider_coef.x = colliderArray[0].GetFloat();
		m_collider_coef.y = colliderArray[1].GetFloat();
	}
}
#pragma endregion

#pragma region "Getters"

math::vec2<>  RigidbodyComponent::GetVelocity() const
{
	return m_velocity;
}

float RigidbodyComponent::GetRotationVelocity() const
{
	return m_rvelocity;
}

float RigidbodyComponent::GetAcceleration() const
{
	return m_acceleration;
}

float RigidbodyComponent::GetMass() const
{
	return m_mass;
}

math::vec2<> RigidbodyComponent::GetColliderScale() const
{
	return m_collider_coef;
}

#pragma endregion

#pragma region "Setters"

void RigidbodyComponent::SetVelocity(math::vec2<> velocity)
{
	m_velocity = velocity;
}

void RigidbodyComponent::SetRotationVelocity(float  rotVelocity)
{
	m_rvelocity = rotVelocity;
}

void RigidbodyComponent::SetAcceleration(float acceleration)
{
	m_acceleration = acceleration;
}

void RigidbodyComponent::SetMass(float  mass)
{
	m_mass = mass;
}

void RigidbodyComponent::GetColliderScale(math::vec2<> scale)
{
	m_collider_coef = scale;
}

void RigidbodyComponent::RegisterToLua(luabridge::lua_State* L)
{
	getGlobalNamespace(L)
		//.deriveClass<TransformComponent, Component>("TransformComponent")
		.beginClass<RigidbodyComponent>("RigidbodyComponent")
		.addConstructor<void(*) (void)>()
		.addFunction("GetComponentType", &RigidbodyComponent::GetComponentType)
		.addProperty("velocity", &RigidbodyComponent::GetVelocity, &RigidbodyComponent::SetVelocity)
		.addProperty("rotationVelocity", &RigidbodyComponent::GetRotationVelocity, &RigidbodyComponent::SetRotationVelocity)
		.addProperty("acceleration", &RigidbodyComponent::GetAcceleration, &RigidbodyComponent::SetAcceleration)
		.addProperty("mass", &RigidbodyComponent::GetMass, &RigidbodyComponent::SetMass)
		.endClass();
}

#pragma endregion