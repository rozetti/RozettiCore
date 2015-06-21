#include "tests.h"

#include <iostream>

class ObjectFunctionTests : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		state = luaL_newstate();
		ASSERT_NE(nullptr, state);
		
		lua_newtable(state);
		ASSERT_TRUE(lua_istable(state, -1));
		
		lua_setglobal(state, "Table");
		lua_getglobal(state, "Table");
		ASSERT_TRUE(lua_istable(state, -1));
	}
	
	lua_State *state;
};

int object_function(lua_State *state)
{
	lua_getfield(state, -1, "HAL");
	auto i = lua_tointeger(state, -1);
	
	std::stringstream ss;
	ss << "HAL" << i;
	
	lua_pushstring(state, ss.str().c_str());
	
	return 1;
}

TEST_F(ObjectFunctionTests, CreateObjectFunction)
{
	lua_pushnumber(state, 9000);
	lua_setfield(state, -2, "HAL");
	ASSERT_TRUE(lua_istable(state, -1));
	
	lua_pushcfunction(state, object_function);
	ASSERT_NE(0, lua_iscfunction(state, -1));
	ASSERT_TRUE(lua_istable(state, -2));
	
	lua_setfield(state, -2, "ObjectFunction");
	ASSERT_TRUE(lua_istable(state, -1));
	
	lua_getfield(state, -1, "ObjectFunction");
	ASSERT_NE(0, lua_iscfunction(state, -1));
	
	lua_getglobal(state, "Table");
	ASSERT_TRUE(lua_istable(state, -1));
	ASSERT_NE(0, lua_iscfunction(state, -2));
	
	ASSERT_EQ(0, lua_pcall(state, 1, 1, 0)) << lua_tostring(state, -1);
	
	EXPECT_NE(0, lua_isstring(state, -1));
	EXPECT_STREQ("HAL9000", lua_tostring(state, -1));
}

TEST_F(ObjectFunctionTests, CallObjectFunctionDotSyntax)
{
	lua_pushnumber(state, 9000);
	lua_setfield(state, -2, "HAL");
	ASSERT_TRUE(lua_istable(state, -1));
	
	lua_pushcfunction(state, object_function);
	ASSERT_NE(0, lua_iscfunction(state, -1));
	ASSERT_TRUE(lua_istable(state, -2));
	
	lua_setfield(state, -2, "ObjectFunction");
	ASSERT_TRUE(lua_istable(state, -1));
	
	auto f = "return Table.ObjectFunction(Table);";
	ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
	ASSERT_EQ(0, lua_pcall(state, 0, 1, 0)) << lua_tostring(state, -1);
	
	EXPECT_NE(0, lua_isstring(state, -1));
	EXPECT_STREQ("HAL9000", lua_tostring(state, -1));
}

TEST_F(ObjectFunctionTests, CallObjectFunctionColonSyntax)
{
	lua_pushnumber(state, 9000);
	lua_setfield(state, -2, "HAL");
	ASSERT_TRUE(lua_istable(state, -1));
	
	lua_pushcfunction(state, object_function);
	ASSERT_NE(0, lua_iscfunction(state, -1));
	ASSERT_TRUE(lua_istable(state, -2));
	
	lua_setfield(state, -2, "ObjectFunction");
	ASSERT_TRUE(lua_istable(state, -1));
	
	auto f = "return Table:ObjectFunction();";
	ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
	ASSERT_EQ(0, lua_pcall(state, 0, 1, 0)) << lua_tostring(state, -1);
	
	EXPECT_NE(0, lua_isstring(state, -1));
	EXPECT_STREQ("HAL9000", lua_tostring(state, -1));
}

