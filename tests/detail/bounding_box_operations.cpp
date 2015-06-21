#include "../../src/rz_core.h"

#include "object_impl.h"

#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>

template <>
void rz::lua_scriptable_object_operations<rz::bounding_box>
	::download(lua_State *state, rz::bounding_box &object)
{
	lua_getfield(state, -1, "min");
	
	lua_getfield(state, -1, "x");
	object.min.x = static_cast<float>(lua_tonumber(state, -1));
	lua_pop(state, 1);
	
	lua_getfield(state, -1, "y");
	object.min.y = static_cast<float>(lua_tonumber(state, -1));
	lua_pop(state, 1);
	
	lua_pop(state, 1);
	lua_getfield(state, -1, "max");
	
	lua_getfield(state, -1, "x");
	object.max.x = static_cast<float>(lua_tonumber(state, -1));
	lua_pop(state, 1);
	
	lua_getfield(state, -1, "y");
	object.max.y = static_cast<float>(lua_tonumber(state, -1));
	lua_pop(state, 1);
	
	lua_pop(state, 1);
}

template <>
void rz::lua_scriptable_object_operations<rz::bounding_box>::upload(lua_State *state, rz::bounding_box const &object)
{
	assert(lua_istable(state, -1));
	
	lua_getfield(state, -1, "min");
	assert(lua_istable(state, -1));
	
	lua_pushnumber(state, object.min.x);
	lua_setfield(state, -2, "x");
	lua_pushnumber(state, object.min.y);
	lua_setfield(state, -2, "y");
	lua_pop(state, 1);
	lua_getfield(state, -1, "max");
	lua_pushnumber(state, object.max.x);
	lua_setfield(state, -2, "x");
	lua_pushnumber(state, object.max.y);
	lua_setfield(state, -2, "y");
	lua_pop(state, 1);
}

template <>
void rz::lua_scriptable_object_operations<rz::bounding_box>::construct(lua_State *state, rz::bounding_box const &object)
{
	assert(lua_istable(state, -1)); // crz: bounding_box
	assert(lua_istable(state, -2)); // crz: ObjectWithBoundingBoxImpl
	
	lua_newtable(state);
	lua_setfield(state, -2, "min");
	lua_newtable(state);
	lua_setfield(state, -2, "max");
	
	rz::lua_scriptable_object_operations<rz::bounding_box>::upload(state, object);
}
