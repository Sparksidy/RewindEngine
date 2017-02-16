/*
File: PostProcessor.cpp
Author: David Westen
Date Created: 1/15/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/

#include <precompiled.h>
#include <Systems/Graphics/PostProcessor.h>

using namespace Graphics;

#pragma region "Constructors/Destructor"

PostProcessor::PostProcessor() : m_previous(nullptr), m_next(nullptr), m_enabled(true)
{

}

PostProcessor::~PostProcessor()
{

}

#pragma endregion

#pragma region "Getters"

bool const & PostProcessor::GetEnabled() const
{
	return m_enabled;
}

#pragma endregion

#pragma region "Setters"

void PostProcessor::SetEnabled(bool const & enabled)
{
	m_enabled = enabled;
}

#pragma endregion