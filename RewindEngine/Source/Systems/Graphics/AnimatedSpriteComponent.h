#pragma once
#include <Engine\Component.h>
#include <Utilities\math\mat3.h>

class Resource;

namespace Graphics
{

	class AnimatedSpriteComponent : public Component
	{
	public:

		friend class AnimationController;

		typedef enum SpriteSheetType
		{
			COLUMN_SPRITE_SHEET,
			ROW_SPRITE_SHEET
		} SpriteSheetType;

		//constructors/destructor
		AnimatedSpriteComponent();
		~AnimatedSpriteComponent();

		//component methods
		void Serialize(JSONObject const & object);

		//getters
		Resource const * const &	GetSpriteSheet() const;
		SpriteSheetType const &		GetType() const;
		unsigned int const &		GetFramesPerElement() const;
		unsigned int const &		GetFrames() const;
		unsigned int const &		GetCurrentFrame() const;

		math::vec2<> const &	GetFrameSize() const;
		float GetSecondsPerFrame() const;

		//setters
		void SetCurrentFrame(unsigned int const & currentFrame);
		void SetSecondsPerFrame(float t);

		//methods
		void NextFrame();
		void PreviousFrame();

		static void RegisterToLua(luabridge::lua_State* L);

	private:

		Resource * m_spriteSheet;
		SpriteSheetType m_type;
		unsigned int m_framesPerElement;
		unsigned int m_frames;
		math::vec2<float> m_frameSize;
		float m_secondsPerFrame;

		float m_counter;
		unsigned int m_currentFrame;


	};

}