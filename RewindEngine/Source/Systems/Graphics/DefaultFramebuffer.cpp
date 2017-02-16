/*
File: DefaultFramebuffer.cpp
Author: David Westen
Date Created: 1/16/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/

#include <precompiled.h>

#include <Systems/Graphics/DefaultFramebuffer.h>

#include <GL/glew.h>

using namespace Graphics;

#pragma region "Constructors/Destructor"

DefaultFramebuffer::DefaultFramebuffer(int const & width, int const & height) : m_width(width), m_height(height)
{
}


DefaultFramebuffer::~DefaultFramebuffer()
{
}

#pragma endregion

#pragma region "Public Methods"

void DefaultFramebuffer::Use()
{
	static GLenum drawBuffers = GL_BACK_LEFT;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDrawBuffers(1, &drawBuffers);
	glViewport(0, 0, m_width, m_height);
}

void DefaultFramebuffer::ClearBuffers()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void DefaultFramebuffer::Resize(int const & width, int const & height)
{
	m_width = width;
	m_height = height;
}

#pragma endregion