#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>

#include "../../src/rz_core.h"

#include "object_impl.h"

template <>
void rz::lua_scriptable_object_operations<Test::interfaces::object_with_bounding_box>
	::construct(lua_State *state, Test::interfaces::object_with_bounding_box const &object)
{
	assert(lua_istable(state, -1));
	
	lua_newtable(state);
	assert(lua_istable(state, -1));
	assert(lua_istable(state, -2));
	
	auto box = object.get_bounding_box();
	rz::lua_scriptable_object_operations<object_type::bounding_box_type>::construct(state, box);
	
	assert(lua_istable(state, -1));
	assert(lua_istable(state, -2));
	
	lua_setfield(state, -2, "bounding_box");
}

template <>
void rz::lua_scriptable_object_operations<Test::interfaces::object_with_bounding_box>
	::print(lua_State *state, Test::interfaces::object_with_bounding_box const &object)
{
	run_lua(state, "print('object_with_bounding_box: " \
		"min=(" \
		"'..ObjectWithBoundingBoxImpl.bounding_box.min.x..', " \
		"'..ObjectWithBoundingBoxImpl.bounding_box.min.y..'), " \
		"max=(" \
		"'..ObjectWithBoundingBoxImpl.bounding_box.max.x..', " \
		"'..ObjectWithBoundingBoxImpl.bounding_box.max.y..')');");
}

template <>
void rz::lua_scriptable_object_operations<Test::interfaces::object_with_bounding_box>
	::upload(lua_State *state, Test::interfaces::object_with_bounding_box const &object)
{
	assert(lua_istable(state, -1));
	
	lua_getfield(state, -1, "bounding_box");
	assert(lua_istable(state, -1));
	
	object_type::bounding_box_type const &box = object.get_bounding_box();
	rz::lua_scriptable_object_operations<object_type::bounding_box_type>::upload(state, box);
	assert(lua_istable(state, -1));
	
	lua_pop(state, 1);
	assert(lua_istable(state, -1));
}

template <>
void rz::lua_scriptable_object_operations<Test::interfaces::object_with_bounding_box>
	::download(lua_State *state, Test::interfaces::object_with_bounding_box &object)
{
	lua_getfield(state, -1, "bounding_box");
	assert(lua_istable(state, -1));
	
	object_type::bounding_box_type box;
	rz::lua_scriptable_object_operations<object_type::bounding_box_type>::download(state, box);
	object.set_bounding_box(box);
	
	lua_pop(state, 1);
	assert(lua_istable(state, -1));
}
