#include "tests.h"

#include <iostream>

TEST(LuaSimpleTest, LoadString)
{
	lua_State *state = luaL_newstate();
	ASSERT_NE(nullptr, state);
	
	int rv = luaL_loadstring(state, "print('hello');");

	ASSERT_EQ(0, rv);
}

TEST(LuaSimpleTest, LoadBadString)
{
	lua_State *state = luaL_newstate();
	luaL_openlibs(state);
	
	int rv = luaL_loadstring(state, "print('hello';");

	ASSERT_NE(0, rv);
	
	auto s = luaL_checkstring(state, 1);
	
	std::cout << "Should be an error message here: " << s;
	ASSERT_NE(nullptr, s);
}

TEST(LuaSimpleTest, RunString)
{
	lua_State *state = luaL_newstate();
	luaL_openlibs(state);
	
	int rv = luaL_loadstring(state, "print('hello');");
	
	ASSERT_EQ(0, rv);

	std::cout << "Should say 'hello' here: ";
	
	rv = lua_pcall(state, 0, LUA_MULTRET, 0);

	ASSERT_EQ(0, rv);
}


