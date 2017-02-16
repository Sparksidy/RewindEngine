/*
File: Framebuffer.cpp
Author: David Westen
Date Created: 1/16/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/

#include <precompiled.h>

#include <Systems/Graphics/Framebuffer.h>

#include <GL/glew.h>

using namespace Graphics;

#pragma region "Constructors/Destructor"

Framebuffer::Framebuffer(int const & width, int const & height) : m_handle(0), m_colorTexture0(0), m_colorTexture1(0), m_width(width), m_height(height)
{
	m_drawBuffers[0] = 0;
	m_drawBuffers[1] = 0;
}


Framebuffer::~Framebuffer()
{

}

#pragma endregion

#pragma region "Public Methods"

void Framebuffer::Use()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
	glDrawBuffers(2, m_drawBuffers);
	glViewport(0, 0, m_width, m_height);
}

void Framebuffer::CreateHandle()
{
	glGenFramebuffers(1, &m_handle);
	glBindFramebuffer(GL_FRAMEBUFFER, m_handle);

	glGenTextures(1, &m_colorTexture0);
	glBindTexture(GL_TEXTURE_2D, m_colorTexture0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorTexture0, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &m_colorTexture1);
	glBindTexture(GL_TEXTURE_2D, m_colorTexture1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_colorTexture1, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	m_drawBuffers[0] = GL_COLOR_ATTACHMENT0;
	m_drawBuffers[1] = GL_COLOR_ATTACHMENT1;

}

void Framebuffer::DestroyHandle()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDeleteTextures(1, &m_colorTexture1);
	glDeleteTextures(1, &m_colorTexture0);
	glDeleteFramebuffers(1, &m_handle);
}

void Framebuffer::ClearBuffers()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Resize(int const & width, int const & height)
{
	m_width = width;
	m_height = height;
	DestroyHandle();
	CreateHandle();
}

#pragma endregion

#pragma region "Getters"

unsigned int const & Framebuffer::GetColorTexture0()
{
	return m_colorTexture0;
}

unsigned int const & Framebuffer::GetColorTexture1()
{
	return m_colorTexture1;
}

int const & Framebuffer::GetWidth()
{
	return m_width;
}

int const & Framebuffer::GetHeight()
{
	return m_height;
}

#pragma endregion