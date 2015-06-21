/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include <string>

#include "rz_core_type_list.h"
#include "rz_core_visitor_pattern.h"

namespace rz
{
	template <class TState, class TObject> class scriptable_object_operations
	{
	public:
		typedef TObject object_type;
		typedef TState state_type;
		
		static void construct(TState *state, TObject const &object);
		static void destruct(TState *state, TObject &object);
		static void print(TState *state, TObject const &object);
		static void upload(TState *state, TObject const &object);
		static void download(TState *state, TObject &object);
	};
	
	template <typename TState>
	struct visitor_policy_base
	{
		typedef TState state_type;
		
		visitor_policy_base(state_type *state) : m_state(state) { }
		~visitor_policy_base() { }
		
	protected:
		state_type *m_state;
	};
}

