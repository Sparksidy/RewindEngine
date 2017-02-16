/*
File: DefaultFramebuffer.h
Author: David Westen
Date Created: 1/17/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/

#pragma once

namespace Graphics
{

	class DefaultFramebuffer
	{
	public:

		//constructors/destructor
		DefaultFramebuffer(int const & width, int const & height);
		~DefaultFramebuffer();

		//public methods
		void Use();
		void ClearBuffers();
		void Resize(int const & width, int const & height);

	private:

		int m_width;
		int m_height;

	};

}