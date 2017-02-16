/*

File: KeyboardManager.cpp
Author: Aakash Chotrani
Date Created:1/23/2017

Purpose(optional):Handles input from keyboard and mouse

*/

#ifndef INPUT_H
#define INPUT_H

//forward declaration
namespace luabridge
{
	struct lua_State;
}


//#include "Core/systems/System.h"
//#include "Core/systems/input/KeyboardManager.h"
//#include "Core/systems/input/GamePad.h"
//#include "Core/systems/input/Mouse.h"

#include "Systems\Core\ISystem.h"
#include "Systems\Input\KeyboardManager.h"
#include"Systems\Input\Mouse.h"

namespace Input
{
	class InputHandler : public ISystem
	{
	public:
		InputHandler(void);
		~InputHandler(void);

		virtual bool Initialize(void) override;
		virtual void Update(float dt) override;
		virtual void Unload(void) override;
		virtual void ReceiveMessage(Message* msg) override;
		virtual std::string GetName(void) const { return "Input"; }

		static void RegisterToLua(luabridge::lua_State* L);
	};

	extern InputHandler* INPUT;
}


#endif