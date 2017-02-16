/*

File: KeyboardManager.cpp
Author: Aakash Chotrani
Date Created:1/23/2017

Purpose(optional):Handles input from keyboard and mouse

*/
#include <precompiled.h>
#include <Systems\Input\Input.h>
#include <stdio.h>
#include <Windows.h>

namespace Input
{
	InputHandler* INPUT = nullptr;

	InputHandler::InputHandler(void)
	{
		INPUT = this;
	}

	InputHandler::~InputHandler(void)
	{

	}

	bool InputHandler::Initialize(void)
	{
		//printf("Input initialized");
		return true;
	}

	void InputHandler::Unload(void)
	{
		printf("Input Unload");
	}

	void InputHandler::Update(float dt)
	{
		//printf("Input update");
	/*	if (GetFocus())
		{
			return;
		}*/
		KeyboardEvent::Update();
		MouseEvent::Update();
	}


	void InputHandler::ReceiveMessage(Message* msg)
	{

	}

	void InputHandler::RegisterToLua(luabridge::lua_State* L)
	{
		KeyboardEvent::RegisterToLua(L);
		MouseEvent::RegisterToLua(L);
	}

}