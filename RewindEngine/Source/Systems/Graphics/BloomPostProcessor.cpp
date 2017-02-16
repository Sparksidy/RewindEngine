/*
File: BloomPostProcessor.cpp
Author: David Westen
Date Created: 1/21/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/

#include <precompiled.h>

#include <Systems/Graphics/BloomPostProcessor.h>
#include <Systems/Graphics/Renderer.h>
#include <Systems/Graphics/PostProcessorChain.h>

#include <GL/glew.h>

using namespace Graphics;

#pragma region "Constructors/Destructor"

BloomPostProcessor::BloomPostProcessor()
{
	m_program.CreateHandle();
	m_program.AttachShader(Program::VERTEX_SHADER_TYPE, "Source/Systems/Graphics/Shaders/BloomPostProcessor.vert");
	m_program.AttachShader(Program::FRAGMENT_SHADER_TYPE, "Source/Systems/Graphics/Shaders/BloomPostProcessor.frag");
	m_program.Link();
}


BloomPostProcessor::~BloomPostProcessor()
{
	m_program.DestroyHandle();
}

#pragma endregion

#pragma region "Public Methods"

void BloomPostProcessor::Apply(Renderer & renderer)
{
	//blur colorBuffer1
	m_program.SetUniform("stage", 0);
	
	for (int i = 0; i < 5; i++)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_chain->GetCurrentInputFramebuffer()->GetColorTexture0());
		m_program.SetUniform("inputTexture", 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_chain->GetCurrentInputFramebuffer()->GetColorTexture1());
		m_program.SetUniform("bloomTexture", 1);

		renderer.RenderScreenQuad(m_program);

		//ping-pong framebuffers
		m_chain->PingPongFramebuffers();
		m_chain->GetCurrentOutputFramebuffer()->Use();
	}

	//combine colorBuffer0 with colorBuffer1
	m_program.SetUniform("stage", 1);
	glBindTexture(GL_TEXTURE_2D, m_chain->GetCurrentInputFramebuffer()->GetColorTexture1());
	
	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D, m_chain->GetCurrentInputFramebuffer()->GetColorTexture0());
	
	renderer.RenderScreenQuad(m_program);
}

#pragma endregion