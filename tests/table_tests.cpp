#include "tests.h"

#include <iostream>

TEST(CreateTableTest, CanCreate)
{
	auto state = luaL_newstate();

	lua_newtable(state);
	EXPECT_TRUE(lua_istable(state, -1));
}

class TableTests : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		state = luaL_newstate();
		ASSERT_NE(nullptr, state);
		
		lua_newtable(state);
		ASSERT_TRUE(lua_istable(state, -1));
	}
	
	lua_State *state;
};

TEST_F(TableTests, CreateTableWithStringKey)
{
	lua_pushstring(state, "answer");
	lua_pushnumber(state, 42);
	lua_settable(state, -3);
	
	lua_pushstring(state, "answer");
	lua_gettable(state, -2);
	
	EXPECT_NE(0, lua_isnumber(state, -1));
	EXPECT_EQ(42, lua_tonumber(state, -1));
}

TEST_F(TableTests, CreateTableWithRawsetStringKey)
{
	lua_pushstring(state, "answer");
	lua_pushnumber(state, 42);
	lua_rawset(state, -3);
	
	lua_pushstring(state, "answer");
	lua_gettable(state, -2);
	
	EXPECT_NE(0, lua_isnumber(state, -1));
	EXPECT_EQ(42, lua_tonumber(state, -1));
}

TEST_F(TableTests, CreateTableWithIntKey)
{
	lua_pushnumber(state, 6);
	lua_pushnumber(state, 9);
	lua_settable(state, -3);
	
	lua_pushnumber(state, 6);
	lua_gettable(state, -2);
	
	EXPECT_NE(0, lua_isnumber(state, -1));
	EXPECT_EQ(9, lua_tonumber(state, -1));
}

TEST_F(TableTests, CreateTableWithRawsetIntKey)
{
	lua_pushnumber(state, 9);
	lua_rawseti(state, -2, 6);
	
	lua_pushnumber(state, 6);
	lua_gettable(state, -2);
	
	EXPECT_NE(0, lua_isnumber(state, -1));
	EXPECT_EQ(9, lua_tonumber(state, -1));
}

TEST_F(TableTests, NameTable)
{
	ASSERT_TRUE(lua_istable(state, -1));
	
	lua_setglobal(state, "Table");
	
	lua_pushnumber(state, 42);
	ASSERT_FALSE(lua_istable(state, -1));
	
	lua_getglobal(state, "Table");
	ASSERT_TRUE(lua_istable(state, -1));
}