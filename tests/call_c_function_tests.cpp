#include "tests.h"

#include <iostream>

class CallCFunctionTests : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		state = luaL_newstate();
		ASSERT_NE(nullptr, state);
	}
	
	lua_State *state;
};

int return_int(lua_State *state)
{
	lua_pushinteger(state, 42);
	
	return 1; // crz: return one value
}

TEST_F(CallCFunctionTests, ReturningInt)
{
	lua_pushcfunction(state, return_int);
	lua_setglobal(state, "return_int");
	
	ASSERT_EQ(0, luaL_loadstring(state, "return return_int();"));
	ASSERT_EQ(0, lua_pcall(state, 0, 1, 0));
	ASSERT_NE(0, lua_isnumber(state, -1));
	ASSERT_EQ(42, lua_tonumber(state, -1));
}

int return_string(lua_State *state)
{
	lua_pushstring(state, "hello");
	
	return 1;
}

TEST_F(CallCFunctionTests, ReturningString)
{
	lua_pushcfunction(state, return_string);
	lua_setglobal(state, "return_string");
	
	ASSERT_EQ(0, luaL_loadstring(state, "return return_string();"));
	ASSERT_EQ(0, lua_pcall(state, 0, 1, 0));
	ASSERT_NE(0, lua_isstring(state, -1));
	ASSERT_STREQ("hello", lua_tostring(state, -1));
}

int return_string_and_int(lua_State *state)
{
	lua_pushstring(state, "hello");
	lua_pushinteger(state, 1729);
	
	return 2; // crz: return two values
}

TEST_F(CallCFunctionTests, ReturningStringAndInt)
{
	lua_pushcfunction(state, return_string_and_int);
	lua_setglobal(state, "return_string_and_int");
	
	auto f = "return return_string_and_int();";
	
	ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
	ASSERT_EQ(0, lua_pcall(state, 0, 2, 0)) << lua_tostring(state, -1);
	
	EXPECT_NE(0, lua_isnumber(state, -1));
	EXPECT_EQ(1729, lua_tonumber(state, -1));

	EXPECT_NE(0, lua_isstring(state, -2));
	EXPECT_STREQ("hello", lua_tostring(state, -2));
}

// todo crz: work out implication of integer/number
int take_int(lua_State *state)
{
	if (!lua_isnumber(state, 1))
	{
		lua_pushnumber(state, 0);
		lua_pushstring(state, "parameter is not number");
		return 2;
	}
	
	lua_pushnumber(state, lua_tonumber(state, 1));
	lua_pushstring(state, "OK");
	
	return 2;
}

TEST_F(CallCFunctionTests, TakingInt)
{
	lua_pushcfunction(state, take_int);
	lua_setglobal(state, "take_int");
	
	auto f = "return take_int(42);";
	
	ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
	ASSERT_EQ(0, lua_pcall(state, 0, LUA_MULTRET, 0)) << lua_tostring(state, -1);
	
	EXPECT_NE(0, lua_isstring(state, -1));
	EXPECT_STREQ("OK", lua_tostring(state, -1));

	EXPECT_NE(0, lua_isnumber(state, -2));
	EXPECT_EQ(42, lua_tonumber(state, -2));
}

TEST_F(CallCFunctionTests, TakingIntAsString)
{
	lua_pushcfunction(state, take_int);
	lua_setglobal(state, "take_int");
	
	ASSERT_EQ(0, luaL_loadstring(state, "a, b = take_int('1729'); return a;"));
	ASSERT_EQ(0, lua_pcall(state, 0, LUA_MULTRET, 0));
	ASSERT_NE(0, lua_isnumber(state, -1));
	EXPECT_EQ(1729, lua_tonumber(state, -1));
	
	ASSERT_EQ(0, luaL_loadstring(state, "a, b = take_int('1729'); return b;"));
	ASSERT_EQ(0, lua_pcall(state, 0, LUA_MULTRET, 0));
	ASSERT_NE(0, lua_isstring(state, -1));
	EXPECT_STREQ("OK", lua_tostring(state, -1));
}

TEST_F(CallCFunctionTests, TakingInvalidInt)
{
	lua_pushcfunction(state, take_int);
	lua_setglobal(state, "take_int");
	
	ASSERT_EQ(0, luaL_loadstring(state, "a, b = take_int('a172'); return a;"));
	ASSERT_EQ(0, lua_pcall(state, 0, LUA_MULTRET, 0));
	ASSERT_NE(0, lua_isnumber(state, -1));
	EXPECT_EQ(0, lua_tonumber(state, -1));
	
	ASSERT_EQ(0, luaL_loadstring(state, "a, b = take_int('a172'); return b;"));
	ASSERT_EQ(0, lua_pcall(state, 0, LUA_MULTRET, 0));
	ASSERT_NE(0, lua_isstring(state, -1));
	EXPECT_STRNE("OK", lua_tostring(state, -1));
}

int take_string(lua_State *state)
{
	if (!lua_isstring(state, 1))
	{
		lua_pushstring(state, "");
		lua_pushstring(state, "parameter is not string");
		return 2;
	}
	
	lua_pushstring(state, lua_tostring(state, 1));
	lua_pushstring(state, "OK");
	
	return 2;
}

TEST_F(CallCFunctionTests, TakingString)
{
	lua_pushcfunction(state, take_string);
	lua_setglobal(state, "take_string");
	
	ASSERT_EQ(0, luaL_loadstring(state, "a, b = take_string('hello'); return a;"));
	ASSERT_EQ(0, lua_pcall(state, 0, LUA_MULTRET, 0));
	ASSERT_NE(0, lua_isstring(state, -1));
	EXPECT_STREQ("hello", lua_tostring(state, 1));
	
	ASSERT_EQ(0, luaL_loadstring(state, "a, b = take_string('hello'); return b;"));
	ASSERT_EQ(0, lua_pcall(state, 0, LUA_MULTRET, 0));
	ASSERT_NE(0, lua_isstring(state, -1));
	EXPECT_STREQ("OK", lua_tostring(state, -1));
}

TEST_F(CallCFunctionTests, TakingStringWithNumber)
{
	lua_pushcfunction(state, take_string);
	lua_setglobal(state, "take_string");
	
	ASSERT_EQ(0, luaL_loadstring(state, "a, b = take_string(1729); return a;"));
	ASSERT_EQ(0, lua_pcall(state, 0, LUA_MULTRET, 0));
	ASSERT_NE(0, lua_isstring(state, -1));
	EXPECT_STREQ("1729", lua_tostring(state, 1));
	
	ASSERT_EQ(0, luaL_loadstring(state, "a, b = take_string(1729); return b;"));
	ASSERT_EQ(0, lua_pcall(state, 0, LUA_MULTRET, 0));
	ASSERT_NE(0, lua_isstring(state, -1));
	EXPECT_STREQ("OK", lua_tostring(state, -1));
}

TEST_F(CallCFunctionTests, TakingStringWithNil)
{
	lua_pushcfunction(state, take_string);
	lua_setglobal(state, "take_string");
	
	ASSERT_EQ(0, luaL_loadstring(state, "a, b = take_string(nil); return a;"));
	ASSERT_EQ(0, lua_pcall(state, 0, LUA_MULTRET, 0));
	ASSERT_NE(0, lua_isstring(state, -1));
	EXPECT_STREQ("", lua_tostring(state, 1));
	
	ASSERT_EQ(0, luaL_loadstring(state, "a, b = take_string(nil); return b;"));
	ASSERT_EQ(0, lua_pcall(state, 0, LUA_MULTRET, 0));
	ASSERT_NE(0, lua_isstring(state, -1));
	EXPECT_STRNE("OK", lua_tostring(state, -1));
}

int take_int_and_string(lua_State *state)
{
	if (!lua_isnumber(state, 1))
	{
		lua_pushnumber(state, 0);
		lua_pushstring(state, "");
		lua_pushstring(state, "first parameter is not number");
		return 3;
	}
	
	if (!lua_isstring(state, 2))
	{
		lua_pushnumber(state, lua_tonumber(state, 1));
		lua_pushstring(state, "");
		lua_pushstring(state, "second parameter is not string");
		return 3;
	}
	
	lua_pushnumber(state, lua_tonumber(state, 1));
	lua_pushstring(state, lua_tostring(state, 2));
	lua_pushstring(state, "OK");
	
	return 3;
}

TEST_F(CallCFunctionTests, TakingIntAndString)
{
	lua_pushcfunction(state, take_int_and_string);
	lua_setglobal(state, "take_int_and_string");
	
	auto f = "return take_int_and_string(1729, 'hello');";
	
	ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
	ASSERT_EQ(0, lua_pcall(state, 0, 3, 0)) << lua_tostring(state, -1);
	
	EXPECT_NE(0, lua_isstring(state, -1));
	EXPECT_STREQ("OK", lua_tostring(state, -1));

	EXPECT_NE(0, lua_isstring(state, -2));
	EXPECT_STREQ("hello", lua_tostring(state, -2));

	EXPECT_NE(0, lua_isnumber(state, -3));
	EXPECT_EQ(1729, lua_tonumber(state, -3));
}

TEST_F(CallCFunctionTests, TakingInvalidIntAndString)
{
	lua_pushcfunction(state, take_int_and_string);
	lua_setglobal(state, "take_int_and_string");
	
	ASSERT_EQ(0, luaL_loadstring(state, "a, b, c = take_int_and_string('a1729', 'hello'); return a;"));
	ASSERT_EQ(0, lua_pcall(state, 0, LUA_MULTRET, 0));
	ASSERT_NE(0, lua_isnumber(state, -1));
	EXPECT_EQ(0, lua_tonumber(state, -1));
	
	ASSERT_EQ(0, luaL_loadstring(state, "a, b, c = take_int_and_string('a1729', 'hello'); return b;"));
	ASSERT_EQ(0, lua_pcall(state, 0, LUA_MULTRET, 0));
	ASSERT_NE(0, lua_isstring(state, -1));
	EXPECT_STREQ("", lua_tostring(state, -1));
	
	ASSERT_EQ(0, luaL_loadstring(state, "a, b, c = take_int_and_string('a1729', 'hello'); return c;"));
	ASSERT_EQ(0, lua_pcall(state, 0, LUA_MULTRET, 0));
	ASSERT_NE(0, lua_isstring(state, -1));
	EXPECT_STRNE("OK", lua_tostring(state, -1));
}


