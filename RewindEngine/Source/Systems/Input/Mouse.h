/*******************************************************************************
* File: Mouse.cpp
* Author: Aakash Chotrani
* Class: GAM 541
******************************************************************************/
#pragma once

namespace Input
{
	struct float2
	{
		float mouseX;
		float mouseY;
	};
  enum MOUSESTATES{LEFT, RIGHT, JUNK,MIDDLE };

  class MouseEvent
  {
  public:

    static void Update(void);
    static void Clear(void);

    static bool IsLeftMouseButtonPressed();
    static bool IsLeftMouseButtonHeld();
    static bool IsLeftMouseButtonReleased();

    static bool IsMiddleMouseButtonPressed();
    static bool IsMiddleMouseButtonHeld();
    static bool IsMiddleMouseButtonReleased();

    static bool IsRightMouseButtonPressed();
    static bool IsRightMouseButtonHeld();
    static bool IsRightMouseButtonReleased();

    static int GetScrollDelta();
    static void SetScollDelta(int delta);
    static void SetMousePosition(int x, int y);

    static float2 GetMousePosition();
    static int GetMouseXPosition();
    static int GetMouseYPosition();

    static float2 GetMouseDelta();

    static void SetLeftMouseButton(bool val);
    static void SetMiddleMouseButton(bool val);
    static void SetRightMouseButton(bool val);

		static void RegisterToLua(luabridge::lua_State* L);

  private:
    static bool m_CurrentKeyStates[3];
    static bool m_PreviousKeyStates[3];
    static int m_ScrollDelta;
    static float2 m_MousePos;
    static float2 m_MouseDelta;
  };
}
