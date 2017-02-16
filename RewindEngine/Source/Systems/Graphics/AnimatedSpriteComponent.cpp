#include "precompiled.h"
#include "AnimatedSpriteComponent.h"

#include <Engine\Engine.h>
#include <Systems\Graphics\GraphicSystem.h>
#include <Systems\Core\ResourceManager.h>
#include <limits>

using namespace Graphics;

#pragma region "Constructors/Destructor"

AnimatedSpriteComponent::AnimatedSpriteComponent() : Component(ANIMATED_SPRITE_COMPONENT), m_spriteSheet(0), m_type(COLUMN_SPRITE_SHEET), m_framesPerElement(0), m_frames(0), m_currentFrame(0), m_frameSize(0, 0), m_secondsPerFrame(0.0f), m_counter(0.0f)
{
}

AnimatedSpriteComponent::~AnimatedSpriteComponent()
{
}

#pragma endregion

#pragma region "Component Methods"

void AnimatedSpriteComponent::Serialize(JSONObject const & object)
{
	auto it = object.FindMember("SpriteSheet");
	if (it != object.MemberEnd())
	{
		//engine.GetResourceManager().GetResource("spritesheet.png");
		ResourceManager * resourceManager = dynamic_cast<ResourceManager*>(Engine::GetEngineSingleton().GetSystem("ResourceManager"));
		m_spriteSheet = resourceManager->GetResource(it->value.GetString());
	}

	it = object.FindMember("Type");
	if (it != object.MemberEnd())
	{
		char const * spriteType = it->value.GetString();
		if(strcmp(spriteType, "Column") == 0)
			m_type = COLUMN_SPRITE_SHEET;
		else
			m_type = ROW_SPRITE_SHEET;
	}

	it = object.FindMember("FramesPerElement");
	if (it != object.MemberEnd())
	{
		m_framesPerElement = it->value.GetInt();
	}

	it = object.FindMember("Frames");
	if (it != object.MemberEnd())
	{
		m_frames = it->value.GetInt();
	}

	it = object.FindMember("CurrentFrame");
	if (it != object.MemberEnd())
	{
		m_currentFrame = it->value.GetInt();
	}

	it = object.FindMember("Duration");
	if (it != object.MemberEnd())
	{
		float duration = it->value.GetFloat();
		m_secondsPerFrame = duration / m_frames;
	}

	//calculate frame size
	switch (m_type) {
	case COLUMN_SPRITE_SHEET:
		m_frameSize.x = 1.0f / (float)((m_frames + (m_framesPerElement - 1)) / m_framesPerElement);
		m_frameSize.y = 1.0f / (float)m_framesPerElement;
		break;
	case ROW_SPRITE_SHEET:
		m_frameSize.x = 1.0f / (float)m_framesPerElement;
		m_frameSize.y = 1.0f / (float)((m_frames + (m_framesPerElement - 1)) / m_framesPerElement);
		break;
	}

}

#pragma endregion

#pragma region "Getters"

Resource const * const & AnimatedSpriteComponent::GetSpriteSheet() const
{
	return m_spriteSheet;
}

typename AnimatedSpriteComponent::SpriteSheetType const & AnimatedSpriteComponent::GetType() const
{
	return m_type;
}

unsigned int const & AnimatedSpriteComponent::GetFramesPerElement() const
{
	return m_framesPerElement;
}

unsigned int const & AnimatedSpriteComponent::GetFrames() const
{
	return m_frames;
}

unsigned int const & AnimatedSpriteComponent::GetCurrentFrame() const
{
	return m_currentFrame;
}

math::vec2<float> const & AnimatedSpriteComponent::GetFrameSize() const
{
	return m_frameSize;
}

#pragma endregion

#pragma region "Setters"

void AnimatedSpriteComponent::SetCurrentFrame(unsigned int const & currentFrame)
{
	m_currentFrame = currentFrame;
}

#pragma endregion

#pragma region "Methods"

void AnimatedSpriteComponent::NextFrame()
{
	m_currentFrame = (m_currentFrame + 1) % m_frames;
}

void AnimatedSpriteComponent::PreviousFrame()
{
	m_currentFrame = (m_currentFrame - 1) % m_frames;
}

float Graphics::AnimatedSpriteComponent::GetSecondsPerFrame()const
{
	return m_secondsPerFrame;
}

void Graphics::AnimatedSpriteComponent::SetSecondsPerFrame(float t)
{
	m_secondsPerFrame = t;
}

void Graphics::AnimatedSpriteComponent::RegisterToLua(luabridge::lua_State* L)
{
	getGlobalNamespace(L)
		.beginClass<AnimatedSpriteComponent>("AnimatedSpriteComponent")
		.addConstructor<void(*) (void)>()
		.addProperty("SecondsPerFrame", &AnimatedSpriteComponent::GetSecondsPerFrame, &AnimatedSpriteComponent::SetSecondsPerFrame)
		.endClass();
}

#pragma endregion