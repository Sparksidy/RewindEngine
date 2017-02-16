#pragma once
#include <Engine\Component.h>
#include <Utilities\math\vec2.h>
class RigidbodyComponent : public Component
{
public:

	//constructors/destructor
	RigidbodyComponent();
	~RigidbodyComponent();

	//component methods
	void Serialize(JSONObject const & object);

	//getters
	math::vec2<> GetVelocity() const;
	float GetRotationVelocity() const;
	float GetAcceleration() const;
	float GetMass() const;
	math::vec2<> GetColliderScale() const;

	//setters
	void SetVelocity(math::vec2<> velocity);
	void SetRotationVelocity(float rotVelocity);
	void SetAcceleration(float acceleration);
	void SetMass(float mass);
	void GetColliderScale(math::vec2<> scale);

	static void RegisterToLua(luabridge::lua_State* L);


	bool m_hasCollision;
	bool m_enableGravity;

private:

	math::vec2<float>	m_velocity;
	float				m_rvelocity;
	float				m_acceleration;
	float				m_mass;
	math::vec2<float>	m_collider_coef;
};

