/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include <string>

#include "rz_core_visitor_pattern.h"

namespace rz
{
	namespace interfaces
	{
		class object_base
		{
		public:
			virtual ~object_base() { }
			
			virtual std::string const get_name() const = 0;
			virtual int get_handle() const = 0;
		};
		
		template <typename TVisitorTypes>
		class visitable_object :
			public virtual object_base,
			public rz::visitable<TVisitorTypes>
		{
		};
		
	}
}
