/*
	FILE:			GameObject.h
	AUTHOR:			Siddharth Gupta
	DATE CREATED:	1/19/17
*/
#pragma once

#include <map>
#include <rapidjson/document.h>

class Component;
class TransformComponent;
class RigidbodyComponent;
namespace Graphics
{
	class SpriteComponent;
	class AnimatedSpriteComponent;
}

class GameObject {

public:

	friend class GameObjectManager;
	friend class Archetype;

	//constructors / destructors
	GameObject();
	~GameObject();

	//public methods
	Component * GetComponent(unsigned int mType);

	//////////////////////////////////////////////////////////////////////////
	//**** Temporary solution****
	TransformComponent* GetTransformComponent();
	Graphics::SpriteComponent* GetSpriteComponent();
	Graphics::AnimatedSpriteComponent* GetAnimatedSpriteComponent();
	RigidbodyComponent* GetRigidbodyComponent();


	//Getters/Setters
	bool GetActive() const;
	void SetActive(bool isActive);
	
	static void RegisterToLua(luabridge::lua_State* L);

private:
	
	typedef rapidjson::GenericObject<false, rapidjson::GenericValue< rapidjson::UTF8<> > > JSONObject;

	void AddComponent(unsigned int mType, JSONObject const & object);
	
	bool m_bActive;
	std::map<unsigned int, Component*> m_Components;

};
