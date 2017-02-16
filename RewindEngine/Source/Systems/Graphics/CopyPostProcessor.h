/*
File: CopyPostProcessor.h
Author: David Westesn
Date Created: 1/17/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/

#pragma once

#include "PostProcessor.h"
#include "Program.h"

namespace Graphics
{

	class CopyPostProcessor : public PostProcessor
	{
	public:

		CopyPostProcessor();
		~CopyPostProcessor();

		void Apply(Renderer & renderer);

	private:

		Program m_program;

	};

}