/*
File: PostProcessorChain.h
Author: David Westen
Date Created: 1/15/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/

#pragma once

namespace Graphics {

	class Renderer;
	class PostProcessor;
	class CopyPostProcessor;

	class DefaultFramebuffer;
	class Framebuffer;

	class PostProcessorChain
	{
	public:

		//constructors/destructor
		PostProcessorChain();
		~PostProcessorChain();

		//public methods
		void Initialize(CopyPostProcessor * copy);
		void Finalize();
		void Append(PostProcessor * postProcessor);
		void Apply(DefaultFramebuffer & defaultFramebuffer, Framebuffer * inputFramebuffer, Framebuffer * outputFramebuffer, Renderer & renderer);
		void PingPongFramebuffers();

		//getters
		Framebuffer * GetCurrentInputFramebuffer() const;
		Framebuffer * GetCurrentOutputFramebuffer() const;

	private:

		Framebuffer * m_currentInputFramebuffer;
		Framebuffer * m_currentOutputFramebuffer;

		PostProcessor * m_head;
		PostProcessor * m_tail;
		int m_size;

	};

}