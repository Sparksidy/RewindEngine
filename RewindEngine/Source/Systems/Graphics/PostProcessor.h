/*
File: PostProcessor.h
Author: David Westen
Date Created: 1/15/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/

#pragma once

#include <Systems/Graphics/Framebuffer.h>

namespace Graphics
{

	class Renderer;

	class PostProcessor
	{
	public:

		friend class PostProcessorChain;

		//constructors/destructor
		PostProcessor();
		virtual ~PostProcessor();

		//public methods
		virtual void Apply(Renderer & renderer) = 0;

		//getters
		bool const & GetEnabled() const;

		//setters
		void SetEnabled(bool const & enabled);

	protected:

		PostProcessorChain * m_chain;

	private:

		PostProcessor * m_previous;
		PostProcessor * m_next;
		bool			m_enabled;

	};

}