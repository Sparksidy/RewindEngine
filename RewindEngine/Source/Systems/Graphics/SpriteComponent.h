#pragma once
#pragma once
#include <Engine\Component.h>

class Resource;

namespace Graphics
{

	class SpriteComponent : public Component
	{
	public:

		//constructors/destructor
		SpriteComponent();
		~SpriteComponent();

		//component methods
		void Serialize(JSONObject const & object);

		//getters
		Resource const * const & GetTexture() const;

	private:

		Resource * m_texture;

	};

}