/*

File: KeyboardManager.cpp
Author: Aakash Chotrani
Date Created:1/23/2017

Purpose(optional):Handles all keyboard events

*/

#include <precompiled.h>
#include <Systems\Input\KeyboardManager.h>

#include <cstring> //memcpy

//Init static variables
bool Input::KeyboardEvent::m_CurrentKeyStates[Input::NUM_KEY_CODES] = { 0 };
bool Input::KeyboardEvent::m_PreviousKeyStates[Input::NUM_KEY_CODES] = { 0 };

namespace Input
{
	void KeyboardEvent::Update(void)
	{

		//printf("keyboard update called \n");

		//Stores the previous key state
		memcpy(m_PreviousKeyStates, m_CurrentKeyStates, sizeof(bool) * VirtualKey::NUM_KEY_CODES);
		

		//Disable warning about forcing a short as a bool
		#pragma warning( push )
		#pragma warning( disable : 4800 )
				for (int i = 0; i < NUM_KEY_CODES; ++i)
				{
					//Gets the current state of the specified key
					m_CurrentKeyStates[i] = GetAsyncKeyState(i);
				}
		#pragma warning (pop)

	}

	void KeyboardEvent::Clear(void)
	{
		memset(m_CurrentKeyStates, false, sizeof(bool) * VirtualKey::NUM_KEY_CODES);
		memset(m_PreviousKeyStates, false, sizeof(bool) * VirtualKey::NUM_KEY_CODES);
	}

	bool KeyboardEvent::IsKeyPressed(int key)
	{
		return (!m_PreviousKeyStates[key] && m_CurrentKeyStates[key]);
	}

	bool KeyboardEvent::IsKeyHeld(int key)
	{
		return (m_PreviousKeyStates[key] && m_CurrentKeyStates[key]);
	}

	bool KeyboardEvent::IsKeyReleased(int key)
	{
		return (m_PreviousKeyStates[key] && !m_CurrentKeyStates[key]);
	}

	void KeyboardEvent::SetKey(int key, bool val)
	{
		m_CurrentKeyStates[key] = val;
	}

	void KeyboardEvent::RegisterToLua(luabridge::lua_State* L)
	{
		getGlobalNamespace(L)
			.beginClass<KeyboardEvent>("KeyboardEvent")
				.addStaticFunction("IsKeyPressed", &Input::KeyboardEvent::IsKeyPressed)
				.addStaticFunction("IsKeyHeld", &Input::KeyboardEvent::IsKeyHeld)
				.addStaticFunction("IsKeyReleased", &Input::KeyboardEvent::IsKeyReleased)
			.endClass();

	}

}