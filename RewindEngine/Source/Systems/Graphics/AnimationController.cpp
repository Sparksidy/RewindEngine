#include "precompiled.h"
#include "AnimationController.h"

#include "AnimatedSpriteComponent.h"

using namespace Graphics;

#pragma region "Constructors/Destructor"

AnimationController::AnimationController()
{
}

AnimationController::~AnimationController()
{
}

#pragma endregion

#pragma region "Public Methods"

void AnimationController::UpdateSprite(AnimatedSpriteComponent & animatedSprite, float const & dt)
{
	animatedSprite.m_counter += dt;
	if (animatedSprite.m_counter >= animatedSprite.m_secondsPerFrame)
	{
		animatedSprite.NextFrame();
		animatedSprite.m_counter = 0.0f;
	}
}

#pragma endregion