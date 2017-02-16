/*

File: precompiled.h
Author: Esteban Enrique Maldonado Cabán
Date Created: January 18, 2017	

Modified by(optional):
Date Modified(optional):

Purpose(optional):

This is the precompiled header that we'll use for the engine. 
This file will need to be included in every .cpp file.
The cool thing

*/

#pragma once
#include <Windows.h>
#include <iostream>

using std::cout;


//STL includes
#include <vector>
#include <map>
#include <unordered_map>
#include <assert.h>
#include <algorithm>
#include <random>
#include <string>


//LUA
#include <Lua/LuaBridge/LuaBridge.h>

extern "C" {
# include <Lua/lua.h>
# include <Lua/lauxlib.h>
# include <Lua/lualib.h>
}

//Math
#include <Utilities/Math/vec2.h>
#include <Utilities/Math/vec3.h>
#include <Utilities/Math/mat3.h>
#include <Utilities/Math/mat4.h>

//HELPFUL MACROS -- (add more if you'd like)
#ifndef SafeDelete
#define SafeDelete(x) { delete x; x = 0; }
#endif

#ifndef SafeDeleteArr
#define SafeDeleteArr(x) { delete [] x; x = 0; }
#endif