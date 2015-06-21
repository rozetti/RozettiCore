/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include "rz_core_lua.h"

#include <iostream>

#include "rz_core_type_list.h"
#include "rz_core_visitor_pattern.h"
#include "rz_core_script_operations.h"

namespace rz
{
	template <class TObject> class lua_scriptable_object_operations
	{
	public:
		typedef TObject object_type;
		
		static void construct(lua_State *state, TObject const &object);
		static void destruct(lua_State *state, TObject &object);
		static void print(lua_State *state, TObject const &object);
		static void upload(lua_State *state, TObject const &object);
		static void download(lua_State *state, TObject &object);
	};

	class lua_scriptable_object_operation_state
	{
		lua_State *m_lua_state;
		
	public:
		lua_scriptable_object_operation_state() : m_lua_state(nullptr) { }
		explicit lua_scriptable_object_operation_state(lua_State *state) : m_lua_state(state) { }
		
		inline void set_lua_state(lua_State *state) { m_lua_state = state; }
		inline lua_State *get_lua_state() const { return m_lua_state; }
	};
	
	struct lua_scriptable_object_visitor_print_policy : public visitor_policy_base<lua_scriptable_object_operation_state>
	{
		lua_scriptable_object_visitor_print_policy(state_type *state) : visitor_policy_base(state) { }
		
		template <class TObject> void visit(TObject &object)
		{
			auto name = object.get_name().c_str();
			std::cout << "lua_scriptable_object_visitor_print_policy::visit(" << name << ")" << std::endl;
			
			auto *state = m_state->get_lua_state();
			
			rz::lua_scriptable_object_operations<TObject>::print(state, object);
		}
	};
	
	struct lua_scriptable_object_visitor_construct_policy : public visitor_policy_base<lua_scriptable_object_operation_state>
	{
		lua_scriptable_object_visitor_construct_policy(state_type *state) : visitor_policy_base(state) { }
		
		template <class TObject> void visit(TObject &object)
		{
			std::cout << "lua_scriptable_object_visitor_construct_policy::visit(" << object.get_name() << ")" << std::endl;
			
			auto *state = m_state->get_lua_state();
			lua_createtable(state, 0, 0);
			
			lua_pushnumber(state, object.get_handle());
			lua_setfield(state, -2, "handle");
			
			rz::lua_scriptable_object_operations<TObject>::construct(state, object);
			rz::lua_scriptable_object_operations<TObject>::upload(state, object);
			
			lua_setglobal(state, object.get_name().c_str());
		}
	};
	
	struct lua_scriptable_object_visitor_destruct_policy : public visitor_policy_base<lua_scriptable_object_operation_state>
	{
		lua_scriptable_object_visitor_destruct_policy(state_type *state) : visitor_policy_base(state) { }
		
		template <class TObject> void visit(TObject &object)
		{
			auto name = object.get_name().c_str();
			std::cout << "lua_scriptable_object_visitor_destruct_policy::visit(" << name << ")" << std::endl;
			
			auto *state = m_state->get_lua_state();
			lua_getglobal(state, name);
			
			rz::lua_scriptable_object_operations<TObject>::destruct(state, object);
			
			lua_pop(state, 1);
			lua_pushnil(state);
			lua_setglobal(state, name);
		}
	};
	
	struct lua_scriptable_object_visitor_upload_policy : public visitor_policy_base<lua_scriptable_object_operation_state>
	{
		lua_scriptable_object_visitor_upload_policy(state_type *state) : visitor_policy_base(state) { }
		
		template <class TObject> void visit(TObject &object)
		{
			auto name = object.get_name().c_str();
			std::cout << "lua_scriptable_object_visitor_upload_policy::visit(" << name << ")" << std::endl;
			
			auto *state = m_state->get_lua_state();
			
			lua_getglobal(state, name);
			rz::lua_scriptable_object_operations<TObject>::upload(state, object);
			lua_pop(state, 1);
		}
	};
	
	struct lua_scriptable_object_visitor_download_policy : public visitor_policy_base<lua_scriptable_object_operation_state>
	{
		lua_scriptable_object_visitor_download_policy(state_type *state) : visitor_policy_base(state) { }
		
		template <class TObject> void visit(TObject &object)
		{
			auto name = object.get_name().c_str();
			std::cout << "lua_scriptable_object_visitor_download_policy::visit(" << name << ")" << std::endl;
			
			auto *state = m_state->get_lua_state();
			
			lua_getglobal(state, name);
			rz::lua_scriptable_object_operations<TObject>::download(state, object);
			lua_pop(state, 1);
		}
	};
}