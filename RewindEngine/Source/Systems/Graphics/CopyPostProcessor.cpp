/*
File: CopyPostProcessor.cpp
Author: David Westen
Date Created: 1/15/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/

#include <precompiled.h>

#include <Systems/Graphics/CopyPostProcessor.h>
#include <Systems/Graphics/PostProcessor.h>
#include <Systems/Graphics/PostProcessorChain.h>
#include <Systems/Graphics/Renderer.h>

#include <GL/glew.h>

using namespace Graphics;

CopyPostProcessor::CopyPostProcessor() : m_program()
{
	m_program.CreateHandle();
	m_program.AttachShader(Program::VERTEX_SHADER_TYPE, "Source/Systems/Graphics/Shaders/CopyPostProcessor.vert");
	m_program.AttachShader(Program::FRAGMENT_SHADER_TYPE, "Source/Systems/Graphics/Shaders/CopyPostProcessor.frag");
	m_program.Link();
}


CopyPostProcessor::~CopyPostProcessor()
{
	m_program.DestroyHandle();
}

void CopyPostProcessor::Apply(Renderer & renderer)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_chain->GetCurrentInputFramebuffer()->GetColorTexture0());
	m_program.SetUniform("inputTexture", 0);
	
	renderer.RenderScreenQuad(m_program);
}