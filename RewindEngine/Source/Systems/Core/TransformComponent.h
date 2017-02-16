#pragma once
#include <Engine\Component.h>
#include <Utilities\math\vec2.h>

class TransformComponent : public Component
{
public:
	
	//constructors/destructor
	TransformComponent();
	~TransformComponent();

	//component methods
	void Serialize(JSONObject const & object);

	//Getters/Setters
	math::vec2<> GetTranslation()const;
	void SetTranslation(math::vec2<> t);

	float GetRotation()const;
	void SetRotation(float rot);

	math::vec2<> GetScale()const;
	void SetScale(math::vec2<> t);

	static void RegisterToLua(luabridge::lua_State* L);

private:
	math::vec2<>	m_translation;
	double m_rotation;
	math::vec2<>	m_scale;
};

