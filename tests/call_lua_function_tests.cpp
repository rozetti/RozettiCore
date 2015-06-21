#include "tests.h"

#include <iostream>

class CallLuaFunctionTests : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		state = luaL_newstate();
		ASSERT_NE(nullptr, state);
	}
	
	lua_State *state;
};

TEST_F(CallLuaFunctionTests, ReturnsString)
{
	auto f = "function ReturnString() return 'hello'; end";
	
	ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
	ASSERT_EQ(0, lua_pcall(state, 0, 0, 0)) << lua_tostring(state, -1);
	
	lua_getglobal(state, "ReturnString");
	
	ASSERT_EQ(0, lua_pcall(state, 0, 1, 0)) << lua_tostring(state, -1);
	
	EXPECT_NE(0, lua_isstring(state, -1));
	EXPECT_STREQ("hello", lua_tostring(state, -1));
}

TEST_F(CallLuaFunctionTests, ReturnsNumber)
{
	auto f = "function ReturnNumber() return 1729; end";
	
	ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
	ASSERT_EQ(0, lua_pcall(state, 0, 0, 0)) << lua_tostring(state, -1);
	
	lua_getglobal(state, "ReturnNumber");
	
	ASSERT_EQ(0, lua_pcall(state, 0, 1, 0)) << lua_tostring(state, -1);
	
	EXPECT_NE(0, lua_isstring(state, -1));
	EXPECT_EQ(1729, lua_tonumber(state, -1));
}

TEST_F(CallLuaFunctionTests, TakesInt)
{
	auto f = "function TakeInt(i) return 2 * i; end";
	
	ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
	ASSERT_EQ(0, lua_pcall(state, 0, 1, 0)) << lua_tostring(state, -1);
	
	lua_getglobal(state, "TakeInt");
	
	lua_pushinteger(state, 21);
	ASSERT_EQ(0, lua_pcall(state, 1, 1, 0)) << lua_tostring(state, -1);
	
	EXPECT_NE(0, lua_isnumber(state, -1));
	EXPECT_EQ(42, lua_tonumber(state, -1));
}

TEST_F(CallLuaFunctionTests, TakesString)
{
	auto f = "function TakeString(s) return '>>'..s..'<<'; end";
	
	ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
	ASSERT_EQ(0, lua_pcall(state, 0, 1, 0)) << lua_tostring(state, -1);
	
	lua_getglobal(state, "TakeString");
	
	lua_pushstring(state, "hello");
	ASSERT_EQ(0, lua_pcall(state, 1, 1, 0)) << lua_tostring(state, -1);
	
	EXPECT_NE(0, lua_isstring(state, -1));
	EXPECT_STREQ(">>hello<<", lua_tostring(state, -1));
}

TEST_F(CallLuaFunctionTests, TakesStringAndInt)
{
	auto f = "function TakeStringAndInt(s, i) return s..i; end";
	
	ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
	ASSERT_EQ(0, lua_pcall(state, 0, 0, 0)) << lua_tostring(state, -1);
	
	lua_getglobal(state, "TakeStringAndInt");
	
	lua_pushstring(state, "HAL");
	lua_pushinteger(state, 9000);
	ASSERT_EQ(0, lua_pcall(state, 2, 1, 0)) << lua_tostring(state, -1);
	
	EXPECT_NE(0, lua_isstring(state, -1));
	EXPECT_STREQ("HAL9000", lua_tostring(state, -1));
}