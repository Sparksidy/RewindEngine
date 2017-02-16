/*******************************************************************************
 * File: Mouse.cpp 
 * Author: Aakash Chotrani	
 * Class: GAM 541
 *****************************************************************************/
#include <precompiled.h>
#include <Systems\Input\Mouse.h>
#include <Windows.h>

namespace Input
{


  void MouseEvent::Update(void)
  {
	//printf("\nMouse update");
    memcpy(m_PreviousKeyStates, m_CurrentKeyStates, sizeof(bool) * 4);
	m_MouseDelta.mouseX = 0.0f;
	m_MouseDelta.mouseY = 0.0f;
   // m_MouseDelta.xy = float2(0.f, 0.f);
    m_ScrollDelta = 0;
    if (MouseEvent::IsLeftMouseButtonHeld())
    {
      int b = 10;
    }

	//Disable warning about forcing a short as a bool
#pragma warning( push )
#pragma warning( disable : 4800 )
	for (int i = 0; i < 4; ++i)
	{
		//Gets the current state of the specified key
		m_CurrentKeyStates[i] = GetAsyncKeyState(i+1);
		//printf("\nm_ currentkeystates[%d]= %d" ,i, m_CurrentKeyStates[i]);
		//printf("\nm_previousKeyStates[%d]= %d" ,i, m_PreviousKeyStates[i]);

	}
#pragma warning (pop)
  }

  void MouseEvent::Clear(void)
  {
    memset(m_CurrentKeyStates, false, sizeof(bool) * 4);
    memset(m_PreviousKeyStates, false, sizeof(bool) * 4);
  }

  bool MouseEvent::IsLeftMouseButtonPressed()
  {
    return (!m_PreviousKeyStates[LEFT] && m_CurrentKeyStates[LEFT]);
  }

  bool MouseEvent::IsLeftMouseButtonHeld()
  {
    return (m_PreviousKeyStates[LEFT] && m_CurrentKeyStates[LEFT]);
  }

  bool MouseEvent::IsLeftMouseButtonReleased()
  {
    return (m_PreviousKeyStates[LEFT] && !m_CurrentKeyStates[LEFT]);
  }

  bool MouseEvent::IsMiddleMouseButtonPressed()
  {
    return (!m_PreviousKeyStates[MIDDLE] && m_CurrentKeyStates[MIDDLE]);
  }

  bool MouseEvent::IsMiddleMouseButtonHeld()
  {
    return (m_PreviousKeyStates[MIDDLE] && m_CurrentKeyStates[MIDDLE]);
  }

  bool MouseEvent::IsMiddleMouseButtonReleased()
  {
    return (m_PreviousKeyStates[MIDDLE] && !m_CurrentKeyStates[MIDDLE]);
  }

  bool MouseEvent::IsRightMouseButtonPressed()
  {
    return (!m_PreviousKeyStates[RIGHT] && m_CurrentKeyStates[RIGHT]);
  }

  bool MouseEvent::IsRightMouseButtonHeld()
  {
    return (m_PreviousKeyStates[RIGHT] && m_CurrentKeyStates[RIGHT]);
  }

  bool MouseEvent::IsRightMouseButtonReleased()
  {
    return (m_PreviousKeyStates[RIGHT] && !m_CurrentKeyStates[RIGHT]);
  }

  int MouseEvent::GetScrollDelta()
  {
    return m_ScrollDelta;
  }

  void MouseEvent::SetScollDelta(int delta)
  {
    m_ScrollDelta = delta;
  }

  void MouseEvent::SetLeftMouseButton(bool val)
  {
    m_CurrentKeyStates[LEFT] = val;
  }

  void MouseEvent::SetMiddleMouseButton(bool val)
  {
    m_CurrentKeyStates[MIDDLE] = val;
  }

  void MouseEvent::SetRightMouseButton(bool val)
  {
    m_CurrentKeyStates[RIGHT] = val;
  }

	void MouseEvent::RegisterToLua(luabridge::lua_State* L)
	{
		getGlobalNamespace(L)
			.beginClass<float2>("float2")
				.addData("mouseX", &Input::float2::mouseX)
				.addData("mouseY", &Input::float2::mouseY)
			.endClass()

			.beginClass<MouseEvent>("MouseEvent")
				.addStaticFunction("IsLeftMouseButtonPressed", &Input::MouseEvent::IsLeftMouseButtonPressed)
				.addStaticFunction("IsLeftMouseButtonHeld", &Input::MouseEvent::IsLeftMouseButtonHeld)
				.addStaticFunction("IsLeftMouseButtonReleased", &Input::MouseEvent::IsLeftMouseButtonReleased)

				.addStaticFunction("IsMiddleMouseButtonPressed", &Input::MouseEvent::IsMiddleMouseButtonPressed)
				.addStaticFunction("IsMiddleMouseButtonHeld", &Input::MouseEvent::IsMiddleMouseButtonHeld)
				.addStaticFunction("IsMiddleMouseButtonReleased", &Input::MouseEvent::IsMiddleMouseButtonReleased)

				.addStaticFunction("IsRightMouseButtonPressed", &Input::MouseEvent::IsRightMouseButtonPressed)
				.addStaticFunction("IsRightMouseButtonHeld", &Input::MouseEvent::IsRightMouseButtonHeld)
				.addStaticFunction("IsRightMouseButtonReleased", &Input::MouseEvent::IsRightMouseButtonReleased)
				
				.addStaticFunction("GetMousePosition", &Input::MouseEvent::GetMousePosition)
				.addStaticFunction("GetMouseDelta", &Input::MouseEvent::GetMouseDelta)

				.addStaticFunction("GetMouseXPosition", &Input::MouseEvent::GetMouseXPosition)
				.addStaticFunction("GetMouseYPosition", &Input::MouseEvent::GetMouseYPosition)
			.endClass();
	}

	void MouseEvent::SetMousePosition(int x, int y)
  {
   // m_MouseDelta = float2(float(x), float(y)) - m_MousePos;
   // m_MousePos = float2(float(x), float(y));

	  m_MouseDelta.mouseX = float(x) - m_MousePos.mouseX;
	  m_MouseDelta.mouseY = float(y) - m_MousePos.mouseX;

	  m_MousePos.mouseX = float(x);
	  m_MousePos.mouseY = float(y);


  }
  POINT p;

  float2 MouseEvent::GetMousePosition()
  {
	  GetCursorPos(&p);
	  m_MousePos.mouseX = p.x;
	  m_MousePos.mouseY = p.y;
    return m_MousePos;
  }

  int MouseEvent::GetMouseXPosition()
  {
	  GetMousePosition();
    return static_cast<int>(m_MousePos.mouseX);
  }

  int MouseEvent::GetMouseYPosition()
  {
	  GetMousePosition();
    return static_cast<int>(m_MousePos.mouseY);
  }

  float2 MouseEvent::GetMouseDelta()
  {
    return m_MouseDelta;
  }

  float2 MouseEvent::m_MouseDelta;

  float2 MouseEvent::m_MousePos;

  int MouseEvent::m_ScrollDelta = 0;

  bool MouseEvent::m_PreviousKeyStates[3];

  bool MouseEvent::m_CurrentKeyStates[3];

}