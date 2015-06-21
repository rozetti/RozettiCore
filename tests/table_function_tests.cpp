#include "tests.h"

#include <iostream>
#include <sstream>

class TableFunctionTexts : public ::testing::Test
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

int table_function(lua_State *state)
{
	lua_pushstring(state, "hello");
	
	return 1;
}

TEST_F(TableFunctionTexts, CreateTableFunction)
{
	lua_pushcfunction(state, table_function);
	ASSERT_NE(0, lua_iscfunction(state, -1));
	
	lua_setfield(state, -2, "TableFunction");
	
	ASSERT_TRUE(lua_istable(state, -1));
	
	lua_getfield(state, -1, "TableFunction");
	ASSERT_NE(0, lua_iscfunction(state, -1));
	
	ASSERT_EQ(0, lua_pcall(state, 0, 1, 0)) << lua_tostring(state, -1);
	
	EXPECT_NE(0, lua_isstring(state, -1));
	EXPECT_STREQ("hello", lua_tostring(state, -1));
}

TEST_F(TableFunctionTexts, CallTableFunction)
{
	lua_pushcfunction(state, table_function);
	ASSERT_NE(0, lua_iscfunction(state, -1));
	
	lua_setfield(state, -2, "TableFunction");
	
	ASSERT_TRUE(lua_istable(state, -1));
	
	auto f = "return Table.TableFunction();";
	ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
	ASSERT_EQ(0, lua_pcall(state, 0, 1, 0)) << lua_tostring(state, -1);
	
	EXPECT_NE(0, lua_isstring(state, -1));
	EXPECT_STREQ("hello", lua_tostring(state, -1));
}

