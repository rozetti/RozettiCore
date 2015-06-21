#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>

#include "../../src/rz_core.h"

#include "objects.h"

static Test::interfaces::object_with_position *p;

int move(lua_State *state);

template <>
void rz::lua_scriptable_object_operations<Test::interfaces::object_with_position>
	::construct(lua_State *state, Test::interfaces::object_with_position const &object)
{
	lua_pushcfunction(state, move);
	lua_setfield(state, -2, "move");
	
	p = const_cast<Test::interfaces::object_with_position *>(&object);
}

template <>
void rz::lua_scriptable_object_operations<Test::interfaces::object_with_position>
	::print(lua_State *state, Test::interfaces::object_with_position const &object)
{
	auto f = "print('object_with_position: x='..ObjectWithPositionImpl.x..', "
	"y='..ObjectWithPositionImpl.y);";
	run_lua(state, f);
}

template <>
void rz::lua_scriptable_object_operations<Test::interfaces::object_with_position>
::upload(lua_State *state, Test::interfaces::object_with_position const &object)
{
	lua_pushnumber(state, object.get_x());
	lua_setfield(state, -2, "x");
	lua_pushnumber(state, object.get_y());
	lua_setfield(state, -2, "y");
}

template <>
void rz::lua_scriptable_object_operations<Test::interfaces::object_with_position>
	::download(lua_State *state, Test::interfaces::object_with_position &object)
{
	lua_getfield(state, -1, "x");
	object.set_x(lua_tonumber(state, -1));
	lua_pop(state, 1);
	
	lua_getfield(state, -1, "y");
	object.set_y(lua_tonumber(state, -1));
	lua_pop(state, 1);
}

#define DOUBLE_PARM(state) lua_tonumber(state, -1); lua_pop(state, 1);

#define OBJECT_HANDLE \
lua_getfield(state, -1, "handle"); \
long handle = lua_tointeger(state, -1); \
lua_pop(state, 1);

#define PARMS_DOUBLE_DOUBLE \
double p2 = DOUBLE_PARM(state); \
double p1 = DOUBLE_PARM(state); \
OBJECT_HANDLE

int move(lua_State *state)
{
	PARMS_DOUBLE_DOUBLE
	
	// todo crz: get pointer from handle
	
	p->move(p1, p2);
	
	rz::lua_scriptable_object_operations<Test::interfaces::object_with_position>::upload(state, *p);
	
	return 0;
}

