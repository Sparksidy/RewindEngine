/*
File: Framebuffer.h
Author: David Westen
Date Created: 1/17/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/

#pragma once

namespace Graphics
{

	class Framebuffer
	{
	public:

		//constructors/destructor
		Framebuffer(int const & width, int const & height);
		~Framebuffer();

		//public methods
		void Use();

		void CreateHandle();
		void DestroyHandle();

		void ClearBuffers();

		void Resize(int const & width, int const & height);

		//getters
		unsigned int const & GetColorTexture0();
		unsigned int const & GetColorTexture1();

		int const & GetWidth();
		int const & GetHeight();

	private:

		unsigned int m_handle;
		unsigned int m_colorTexture0;
		unsigned int m_colorTexture1;

		int m_width;
		int m_height;

		unsigned int m_drawBuffers[2];

	};

}