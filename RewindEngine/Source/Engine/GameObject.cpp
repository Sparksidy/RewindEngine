
#include <precompiled.h>
#include <Engine\GameObject.h>
#include <Engine\Component.h>

#include <Systems\Core\TransformComponent.h>
#include <Systems\Graphics\SpriteComponent.h>
#include <Systems\Graphics\AnimatedSpriteComponent.h>
#include <Systems\Physics\RigidbodyComponent.h>
#include <Systems/Scripting/Components/LuaScriptComponent.h>


#pragma region "Constructors/ Destructors"

GameObject::GameObject() : m_bActive(true), m_Components()
{
}
GameObject::~GameObject()
{
	
}
#pragma endregion

Component *  GameObject::GetComponent(unsigned int mType)
{
	//Get the type of component by specifying the type of component
	if (m_Components.count(mType))
		return m_Components[mType];
	else
		return nullptr;
}

void GameObject::AddComponent(unsigned int mType, JSONObject const & object)
{

	Component* newComponent = nullptr;
	switch (mType)
	{
		case TRANSFORM_COMPONENT:
			newComponent = new TransformComponent();
			break;
		case SPRITE_COMPONENT:
			newComponent = new Graphics::SpriteComponent();
			break;
		case ANIMATED_SPRITE_COMPONENT:
			newComponent = new Graphics::AnimatedSpriteComponent();
			break;
		case LUA_SCRIPT_COMPONENT:
			newComponent = new LuaScriptComponent();
			break;
		case RIGIDBODY_COMPONENT:
			newComponent = new RigidbodyComponent();
			break;
	}

	if (newComponent)
	{
		newComponent->SetOwner(this);
		newComponent->Serialize(object);
		m_Components[mType] = newComponent;
	}
}


#pragma endregion

#pragma region "Getters/Setters"

bool GameObject::GetActive() const
{
	return m_bActive;
}

void GameObject::SetActive(bool isActive)
{
	m_bActive = isActive;
}

TransformComponent* GameObject::GetTransformComponent()
{
	return (TransformComponent*)GetComponent(TRANSFORM_COMPONENT);
}

Graphics::SpriteComponent* GameObject::GetSpriteComponent()
{
	return (Graphics::SpriteComponent*)GetComponent(SPRITE_COMPONENT);
}

Graphics::AnimatedSpriteComponent* GameObject::GetAnimatedSpriteComponent()
{
	return (Graphics::AnimatedSpriteComponent*)GetComponent(ANIMATED_SPRITE_COMPONENT);
}

RigidbodyComponent* GameObject::GetRigidbodyComponent()
{
	return(RigidbodyComponent*)GetComponent(RIGIDBODY_COMPONENT);
}

void GameObject::RegisterToLua(luabridge::lua_State* L)
{
	getGlobalNamespace(L)
		.beginClass<GameObject>("GameObject")
			.addProperty("IsActive", &GameObject::GetActive, &GameObject::SetActive)
			.addFunction("GetTransformComponent", &GameObject::GetTransformComponent)
			.addFunction("GetSpriteComponent", &GameObject::GetSpriteComponent)
			.addFunction("GetAnimatedSpriteComponent", &GameObject::GetAnimatedSpriteComponent)
			.addFunction("GetRigidbodyComponent",&GameObject::GetRigidbodyComponent)
		.endClass();
}

#pragma endregion