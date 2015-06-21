#include "tests.h"

#include <iostream>
#include <vector>
#include <algorithm>

namespace
{
	struct ObjectBase
	{
		ObjectBase(int _handle, std::string const &_name) : handle(_handle), name(_name) { }
		virtual ~ObjectBase() { }
		int handle;
		std::string name;
	};
	
	struct Object : public ObjectBase
	{
		double x, y;
		
		Object(int _handle, double _x, double _y) : x(_x), y(_y), ObjectBase(_handle, "object")	{ }
	};
	
	struct OtherObject : public ObjectBase
	{
		double w, h;
		
		OtherObject(int _handle, double _w, double _h) :
			w(_w), h(_h), ObjectBase(_handle, "otherobject")
		{ }
	};
	
	int get_x(lua_State *);
	int set_x(lua_State *);
	
	class ObjectRetrievalTests : public ::testing::Test
	{
	protected:
		ObjectRetrievalTests() :
		state(nullptr),
		object1(nullptr),
		otherobject1(nullptr)
		{
		}
		
		virtual void SetUp()
		{
			state = luaL_newstate();
			ASSERT_NE(nullptr, state);
			
			luaL_openlibs(state); // crz: for print()
			
			object1 = new Object(1, 4.2, 1.729);
			otherobject1 = new OtherObject(2, 0.618, 1.618);
			
			objects.clear();
			objects.push_back(object1);
			objects.push_back(otherobject1);
			
			for (auto p : objects)
			{
				lua_newtable(state);
				lua_pushinteger(state, p->handle);
				lua_setfield(state, -2, "handle");
				lua_setglobal(state, p->name.c_str());
			}
			
			lua_getglobal(state, "object");
			ASSERT_TRUE(lua_istable(state, -1));
			
			lua_pushcfunction(state, get_x);
			lua_setfield(state, -2, "getX");
			ASSERT_TRUE(lua_istable(state, -1));
			
			lua_pushcfunction(state, set_x);
			lua_setfield(state, -2, "setX");
			ASSERT_TRUE(lua_istable(state, -1));
		}
		
		virtual void TearDown()
		{
			delete object1;
			delete otherobject1;
		}
		
	protected:
		lua_State *state;
		Object *object1;
		OtherObject *otherobject1;
		
	public:
		static std::vector<ObjectBase *> objects;
	};
	
	std::vector<ObjectBase *> ObjectRetrievalTests::objects;
	
	int get_x(lua_State *state)
	{
		lua_getfield(state, -1, "handle");
		int handle = static_cast<int>(lua_tointeger(state, -1));
		
		auto p = std::find_if(
							  ObjectRetrievalTests::objects.begin(),
							  ObjectRetrievalTests::objects.end(), [handle](ObjectBase *p)
							  {
								  return p->handle ==  handle;
							  });
		
		auto o = static_cast<Object *>(*p);
		
		lua_pushnumber(state, o->x);
		
		return 1;
	}
	
	int set_x(lua_State *state)
	{
		std::cout << "-1: " << lua_typename(state, lua_type(state, -1)) << std::endl << std::flush;
		std::cout << "-2: " << lua_typename(state, lua_type(state, -2)) << std::endl << std::flush;
		
		double x = lua_tonumber(state, -1);
		lua_pop(state, 1);
		
		lua_getfield(state, -1, "handle");
		int handle = static_cast<int>(lua_tointeger(state, -1));
		
		auto p = std::find_if(
							  ObjectRetrievalTests::objects.begin(),
							  ObjectRetrievalTests::objects.end(), [handle](ObjectBase *p)
							  {
								  return p->handle ==  handle;
							  });

		auto o = static_cast<Object *>(*p);
		
		lua_pushnumber(state, o->x);

		o->x = x;
		
		return 0;
	}
	
	TEST_F(ObjectRetrievalTests, ObjectAndHandleMocksWorkOK)
	{
		ASSERT_DOUBLE_EQ(4.2, object1->x);
		ASSERT_DOUBLE_EQ(1.729, object1->y);

		ASSERT_DOUBLE_EQ(0.618, otherobject1->w);
		ASSERT_DOUBLE_EQ(1.618, otherobject1->h);
	}
	
	TEST_F(ObjectRetrievalTests, AccessObjectFromLua)
	{
		auto f = "return object:getX();";
		ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
		ASSERT_EQ(0, lua_pcall(state, 0, 1, 0)) << lua_tostring(state, -1);
		
		ASSERT_NE(0, lua_isnumber(state, -1));
		double x = lua_tonumber(state, -1);
		
		ASSERT_DOUBLE_EQ(4.2, x);
	}
	
	TEST_F(ObjectRetrievalTests, UpdateObjectFromLua)
	{
		ASSERT_DOUBLE_EQ(4.2, object1->x);
		
		auto f = "object:setX(3.14);";
		ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
		ASSERT_EQ(0, lua_pcall(state, 0, 0, 0)) << lua_tostring(state, -1);
		
		ASSERT_DOUBLE_EQ(3.14, object1->x);
	}
	
	TEST_F(ObjectRetrievalTests, LoadLuaObjectBeforeCall)
	{
		lua_getglobal(state, "object");
		ASSERT_TRUE(lua_istable(state, -1));
		
		lua_pushnumber(state, object1->x);
		lua_setfield(state, -2, "x");
		ASSERT_TRUE(lua_istable(state, -1));
		
		lua_pushnumber(state, object1->y);
		lua_setfield(state, -2, "y");
		ASSERT_TRUE(lua_istable(state, -1));
		
		auto f = "return object.x, object.y;";
		ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
		ASSERT_EQ(0, lua_pcall(state, 0, 2, 0));
		
		double y = lua_tonumber(state, -1);
		double x = lua_tonumber(state, -2);
		
		ASSERT_DOUBLE_EQ(object1->x, x);
		ASSERT_DOUBLE_EQ(object1->y, y);
	}
	
	TEST_F(ObjectRetrievalTests, SaveLuaObjectAfterCall)
	{
		auto f = "object.x = 1.23; object.y = 2.34;";
		ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
		ASSERT_EQ(0, lua_pcall(state, 0, 0, 0)) << lua_tostring(state, -1);
		
		lua_getglobal(state, "object");
		ASSERT_TRUE(lua_istable(state, -1));
		
		lua_getfield(state, -1, "x");
		ASSERT_NE(0, lua_isnumber(state, -1));
		double x = lua_tonumber(state, -1);
		lua_pop(state, 1);
		ASSERT_TRUE(lua_istable(state, -1));
		
		lua_getfield(state, -1, "y");
		ASSERT_NE(0, lua_isnumber(state, -1));
		double y = lua_tonumber(state, -1);
		lua_pop(state, 1);
		ASSERT_TRUE(lua_istable(state, -1));
		
		double old_x = object1->x;
		double old_y = object1->y;
		
		object1->x = x;
		object1->y = y;
		
		ASSERT_DOUBLE_EQ(4.2, old_x);
		ASSERT_DOUBLE_EQ(1.729, old_y);
		ASSERT_DOUBLE_EQ(1.23, object1->x);
		ASSERT_DOUBLE_EQ(2.34, object1->y);
	}
	
	TEST_F(ObjectRetrievalTests, ObjectStateReflectsCall)
	{
		lua_getglobal(state, "object");
		
		lua_pushnumber(state, object1->x);
		lua_setfield(state, -2, "x");
		lua_pushnumber(state, object1->y);
		lua_setfield(state, -2, "y");
		
		ASSERT_TRUE(lua_istable(state, -1));
		
		lua_getfield(state, -1, "x");
		ASSERT_EQ(object1->x, lua_tonumber(state, -1));
		lua_pop(state, 1);
		
		lua_getfield(state, -1, "y");
		ASSERT_EQ(object1->y, lua_tonumber(state, -1));
		lua_pop(state, 1);
		
		ASSERT_TRUE(lua_istable(state, -1));
		
		auto f = "object.x = object.x * 2; object.y = object.y * 2;";
		ASSERT_EQ(0, luaL_loadstring(state, f)) << lua_tostring(state, -1);
		ASSERT_EQ(0, lua_pcall(state, 0, 0, 0)) << lua_tostring(state, -1);
		
		ASSERT_TRUE(lua_istable(state, -1));
		
		lua_getfield(state, -1, "x");
		object1->x = lua_tonumber(state, -1);
		lua_pop(state, 1);
		
		lua_getfield(state, -1, "y");
		object1->y = lua_tonumber(state, -1);
		lua_pop(state, 1);
		
		ASSERT_DOUBLE_EQ(4.2 * 2, object1->x);
		ASSERT_DOUBLE_EQ(1.729 * 2, object1->y);
	}
}
