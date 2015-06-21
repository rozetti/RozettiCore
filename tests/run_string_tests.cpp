#include "tests.h"

#include <iostream>

class LuaRunStringTests : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		state = luaL_newstate();
		ASSERT_NE(nullptr, state);

		// todo crz: find out why we need this to call functions
		luaL_openlibs(state);
	}
	
	lua_State *state;
};

// todo crz: capture and test stdout
TEST_F(LuaRunStringTests, RunStringWithFunction)
{
	ASSERT_EQ(0, luaL_loadstring(state, "function do_print(m) print(m); end do_print('apple');"));

	std::cout << "Should say 'apple' here: ";
	ASSERT_EQ(0, lua_pcall(state, 0, 0, 0)) << lua_tostring(state, -1);
}

TEST_F(LuaRunStringTests, RunStringReturnsInt)
{
	ASSERT_EQ(0, luaL_loadstring(state, "return 3;"));
	ASSERT_EQ(0, lua_pcall(state, 0, LUA_MULTRET, 0));
	ASSERT_NE(0, lua_isnumber(state, -1));
	ASSERT_EQ(3, lua_tointeger(state, -1));
}

TEST_F(LuaRunStringTests, RunStringReturnsString)
{
	ASSERT_EQ(0, luaL_loadstring(state, "return 'hello';"));
	ASSERT_EQ(0, lua_pcall(state, 0, LUA_MULTRET, 0));
	ASSERT_NE(0, lua_isstring(state, -1));
	ASSERT_STREQ("hello", lua_tostring(state, -1));
}

TEST_F(LuaRunStringTests, RunStringReturnsStringAndInt)
{
	auto f = "return 'hello', 42;";
	
	ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
	ASSERT_EQ(0, lua_pcall(state, 0, 2, 0)) << lua_tostring(state, -1);
	
	EXPECT_NE(0, lua_isnumber(state, -1));
	EXPECT_EQ(42, lua_tonumber(state, -1));
	
	EXPECT_NE(0, lua_isstring(state, -2));
	EXPECT_STREQ("hello", lua_tostring(state, -2));
}

