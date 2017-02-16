/*
File: Window.h
Author: David Westen
Date Created: 1/15/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/

#pragma once

#include <Windows.h>
#include <map>

namespace Graphics
{

	class Window
	{
	public:

		//constructors/destructors
		Window(int width, int height, char const * title);
		~Window();

		//public methods
		void MakeCurrent() const;
		void SwapBuffers() const;

	private:

		//static wndproc router
		static LRESULT CALLBACK WndProcRouter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


		//managed objects
		HWND		m_handle;
		HDC			m_device;
		HGLRC		m_context;

	};

}