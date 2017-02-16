#include "precompiled.h"
#include "SpriteComponent.h"

#include <Systems\Graphics\GraphicSystem.h>
#include <Engine\Engine.h>
#include <Systems\Core\ResourceManager.h>

using namespace Graphics;

#pragma region "Constructors/Destructor"

SpriteComponent::SpriteComponent() : Component(SPRITE_COMPONENT), m_texture(0)
{

}


SpriteComponent::~SpriteComponent()
{

}

#pragma endregion

#pragma region "Component Methods"

void SpriteComponent::Serialize(JSONObject const & object)
{

	auto it = object.FindMember("Texture");
	if (it != object.MemberEnd())
	{
		ResourceManager * resourceManager = dynamic_cast<ResourceManager*>(Engine::GetEngineSingleton().GetSystem("ResourceManager"));
		m_texture = resourceManager->GetResource(it->value.GetString());
	}

}

#pragma endregion

#pragma region "Getters"

Resource const * const & SpriteComponent::GetTexture() const
{
	return m_texture;
}

#pragma endregion