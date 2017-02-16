#include <precompiled.h>

/*
File: PostProcessorChain.cpp
Author: David Westen
Date Created: 1/15/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/


#include <Systems/Graphics/PostProcessorChain.h>

#include <Systems/Graphics/DefaultFramebuffer.h>
#include <Systems/Graphics/Framebuffer.h>
#include <Systems/Graphics/PostProcessor.h>
#include <Systems/Graphics/CopyPostProcessor.h>

#include <GL/glew.h>

using namespace Graphics;

#pragma region "Constructors/Destructor"

PostProcessorChain::PostProcessorChain() : m_currentInputFramebuffer(nullptr), m_currentOutputFramebuffer(nullptr), m_head(nullptr), m_tail(nullptr), m_size(0)
{

}


PostProcessorChain::~PostProcessorChain()
{

}

#pragma endregion

#pragma region "Public Methods"

void PostProcessorChain::Initialize(CopyPostProcessor * copy)
{

	m_head = copy;
	m_tail = copy;
	m_size = 1;

	copy->m_chain = this;
}

void PostProcessorChain::Finalize()
{
	PostProcessor * current = m_head;
	while (current)
	{
		PostProcessor * temp = current;
		current = current->m_next;
		delete temp;
	}
}

void PostProcessorChain::Append(PostProcessor * postProcessor)
{
	if (m_size == 1)
	{
		m_head = postProcessor;
		m_head->m_next = m_tail;
		m_tail->m_previous = m_head;
	}
	else if (m_size == 2)
	{
		m_head->m_previous = postProcessor;
		postProcessor->m_next = m_head;
		m_head = postProcessor;
	}
	else
	{
		m_tail->m_previous->m_next = postProcessor;
		postProcessor->m_previous = m_tail->m_previous;
		postProcessor->m_next = m_tail;
		m_tail->m_previous = postProcessor;
	}

	postProcessor->m_chain = this;
	m_size++;
}

void PostProcessorChain::Apply(DefaultFramebuffer & defaultFramebuffer, Framebuffer * inputFramebuffer, Framebuffer * outputFramebuffer, Renderer & renderer)
{
	//start with the framebuffer where the scene was renderered to
	m_currentInputFramebuffer = inputFramebuffer;
	m_currentOutputFramebuffer = outputFramebuffer;

	//walk the linked list and apply each post processing effect, if active
	PostProcessor * current = m_head;
	while (current->m_next)
	{
		if (current->GetEnabled())
		{
			m_currentOutputFramebuffer->Use();
			current->Apply(renderer);
			PingPongFramebuffers();
			current = current->m_next;
		}
	}

	//last post processing effect copies result to screen
	defaultFramebuffer.Use();
	m_tail->Apply(renderer);
}

//swap input and output framebuffers
void PostProcessorChain::PingPongFramebuffers()
{
	Framebuffer * temp = m_currentInputFramebuffer;
	m_currentInputFramebuffer = m_currentOutputFramebuffer;
	m_currentOutputFramebuffer = temp;
}

#pragma endregion

#pragma region "Getters"

Framebuffer * PostProcessorChain::GetCurrentInputFramebuffer() const
{
	return m_currentInputFramebuffer;
}

Framebuffer * PostProcessorChain::GetCurrentOutputFramebuffer() const
{
	return m_currentOutputFramebuffer;
}

#pragma endregion