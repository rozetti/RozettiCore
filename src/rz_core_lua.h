/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

extern "C"
{
#include "../third_party/lua/lua.h" 
#include "../third_party/lua/lualib.h" 
#include "../third_party/lua/lauxlib.h" 
}

#include <string>

struct lua_State;

namespace rz
{
	bool run_lua(lua_State *state, std::string const &code);
}