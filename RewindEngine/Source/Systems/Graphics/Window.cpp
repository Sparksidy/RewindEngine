/*
File: Window.cpp
Author: David Westen
Date Created: 1/15/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/

#include "../Source/precompiled.h"
#include <Engine\Engine.h>
#include <Systems/Graphics/Window.h>

#include <cstring>


#pragma region "Static Data"

char const * const  s_windowClassName = "WindowClassName";
WNDCLASSEX s_windowClass;

LRESULT CALLBACK Graphics::Window::WndProcRouter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	return Engine::GetEngineSingleton().MessageHandler(hWnd, msg, wParam, lParam);
	//return DefWindowProc(hWnd, msg, wParam, lParam);
}

#pragma endregion

#pragma region "Constructors/Destructors"

Graphics::Window::Window(int width, int height, char const * title) : m_handle(0), m_device(0), m_context(0)
{
	s_windowClass.cbSize = sizeof(WNDCLASSEX);
	s_windowClass.style = CS_OWNDC;
	s_windowClass.lpfnWndProc = WndProcRouter;
	s_windowClass.cbClsExtra = 0;
	s_windowClass.cbWndExtra = 0;
	s_windowClass.hInstance = GetModuleHandle(NULL);
	s_windowClass.hIcon = NULL;
	s_windowClass.hCursor = LoadCursor(s_windowClass.hInstance, IDC_ARROW);
	s_windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	s_windowClass.lpszMenuName = NULL;
	s_windowClass.lpszClassName = s_windowClassName;
	s_windowClass.hIconSm = NULL;

	if (!RegisterClassEx(&s_windowClass))
	{
			//report error
		MessageBox(NULL, "Failed to register window", "Error!", MB_OK);
	}

	m_handle = CreateWindowEx(0, s_windowClassName, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, GetModuleHandle(NULL), NULL);

	if (!m_handle)
	{
		//report error
		MessageBox(NULL, "Failed to create window", "Error!", MB_OK);
	}

	UpdateWindow(m_handle);
	ShowWindow(m_handle, SW_SHOW);

	m_device = GetDC(m_handle);

	PIXELFORMATDESCRIPTOR pfd;
	std::memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 0;
	pfd.cStencilBits = 0;

	int formatIndex = ChoosePixelFormat(m_device, &pfd);
	SetPixelFormat(m_device, formatIndex, &pfd);

	m_context = wglCreateContext(m_device);

	if (!m_context)
	{
		MessageBox(NULL, "Failed to create opengl context", "Error!", MB_OK);
	}

}

Graphics::Window::~Window()
{
	wglMakeCurrent(m_device, NULL);
	wglDeleteContext(m_context);
	UnregisterClass(s_windowClassName, GetModuleHandle(NULL));
}

#pragma endregion

#pragma region "Public Methods"

void Graphics::Window::MakeCurrent() const
{
	wglMakeCurrent(m_device, m_context);
}

void Graphics::Window::SwapBuffers() const
{
	::SwapBuffers(m_device);
}

#pragma endregion