/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include <functional>

namespace rz
{
	class finally
	{
	public:
		finally(std::function<void()> f) :
			code(f),
			cancelled(false)
		{
		}
		
		~finally()
		{
			if (!cancelled)
			{
				code();
			}
		}
		
		void cancel()
		{
			cancelled = true;
		}
		
	private:
		finally(finally const &);
		finally &operator=(finally const &);
		
		std::function<void()> code;
		bool cancelled;
	};
}
