/*
	FILE:			Component.h
	AUTHOR:			Siddharth Gupta
	DATE CREATED:	1/19/17
*/

#pragma once

/*
Abstract base class for the components
GameObjects are composed of components
Various components will inherit from the component class
*/

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

class GameObject;

enum COMPONENT_TYPE : unsigned int {

	//List the components here after creating them 
	//Core
	TRANSFORM_COMPONENT,

	//Graphics
	SPRITE_COMPONENT,
	ANIMATED_SPRITE_COMPONENT,

	//Physics
	RIGIDBODY_COMPONENT,

	//Scripting
	LUA_SCRIPT_COMPONENT,

	NUM_COMPONENTS
};

class Component {

public:
	typedef rapidjson::GenericObject<false, rapidjson::GenericValue<rapidjson::UTF8<>>> JSONObject;

	//constructors/destructors
	Component(unsigned int Type);
	virtual ~Component() {};

	//Getters/Setters
	unsigned int GetComponentType();
	GameObject* GetOwner() { return m_pOwner; }
	void SetOwner(GameObject* go) { m_pOwner = go; }

	//Serializing the component from a text or json file
	virtual void Serialize(JSONObject const & object) {};


	static void RegisterToLua(luabridge::lua_State* L);

protected:
	GameObject* m_pOwner;
	unsigned int m_ComponentType;
};
