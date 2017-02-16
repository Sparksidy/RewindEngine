/*
File: BloomPostProcessor.h
Author: David Westen
Date Created: 1/21/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/

#pragma once

#include <Systems/Graphics/PostProcessor.h>
#include <Systems/Graphics/Program.h>

namespace Graphics
{

	class BloomPostProcessor : public PostProcessor
	{
	public:

		//constructors/destructor
		BloomPostProcessor();
		~BloomPostProcessor();

		//public methods
		void Apply(Renderer & renderer);

	private:

		Program m_program;

	};

}