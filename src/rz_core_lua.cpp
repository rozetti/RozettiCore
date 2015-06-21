/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core_lua.h"
#include <string>
#include <iostream>

bool rz::run_lua(lua_State *state, std::string const &code)
{
	if (0 != luaL_loadstring(state, code.c_str()))
	{
		std::cout << "luaL_loadstring failed: " << lua_tostring(state, -1) << std::endl;
		return false;
	}
	
	if (0 != lua_pcall(state, 0, 0, 0))
	{
		std::cout << "lua_pcall failed: " << lua_tostring(state, -1) << std::endl;
		return false;
	}
	
	return true;
}

