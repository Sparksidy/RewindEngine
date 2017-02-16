#pragma once

namespace Graphics
{
	class AnimatedSpriteComponent;

	class AnimationController
	{
	public:

		//constructors/destructor
		AnimationController();
		~AnimationController();

		//public methods
		void UpdateSprite(AnimatedSpriteComponent & animatedSprite, float const & dt);

	};
}