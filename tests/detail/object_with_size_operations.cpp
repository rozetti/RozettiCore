#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>

#include "../../src/rz_core.h"

#include "objects.h"

static Test::interfaces::object_with_size *p;

int resize(lua_State *state);

template <>
void rz::lua_scriptable_object_operations<Test::interfaces::object_with_size>
::construct(lua_State *state, Test::interfaces::object_with_size const &object)
{
	lua_pushcfunction(state, resize);
	lua_setfield(state, -2, "resize");
	
	p = const_cast<Test::interfaces::object_with_size *>(&object);
}

template <>
void rz::lua_scriptable_object_operations<Test::interfaces::object_with_size>
	::print(lua_State *state, Test::interfaces::object_with_size const &object)
{
	auto f = "print('object_with_size: w='..ObjectWithSizeImpl.w..', "
	"h='..ObjectWithSizeImpl.h);";
	run_lua(state, f);
}

template <>
void rz::lua_scriptable_object_operations<Test::interfaces::object_with_size>
	::upload(lua_State *state, Test::interfaces::object_with_size const &object)
{
	lua_pushnumber(state, object.get_w());
	lua_setfield(state, -2, "w");
	lua_pushnumber(state, object.get_h());
	lua_setfield(state, -2, "h");
}

template <>
void rz::lua_scriptable_object_operations<Test::interfaces::object_with_size>
	::download(lua_State *state, Test::interfaces::object_with_size &object)
{
	lua_getfield(state, -1, "w");
	object.set_w(lua_tonumber(state, -1));
	lua_pop(state, 1);
	
	lua_getfield(state, -1, "h");
	object.set_h(lua_tonumber(state, -1));
	lua_pop(state, 1);
}

int resize(lua_State *state)
{
	double p2 = lua_tonumber(state, -1);
	lua_pop(state, 1);
	double p1 = lua_tonumber(state, -1);
	lua_pop(state, 1);
	
	lua_getfield(state, -1, "handle");
	long handle = lua_tointeger(state, -1);
	lua_pop(state, 1);
	
	// todo crz: get pointer from handle
	
	p->resize(p1, p2);
	
	rz::lua_scriptable_object_operations<Test::interfaces::object_with_size>::upload(state, *p);
	
	return 0;
}
