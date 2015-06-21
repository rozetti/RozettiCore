/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

namespace rz
{
	template <typename T>
	class modify_policy
	{
		T *get(T *current)
		{
			return current;
		}
	};

	template <typename T>
	class new_policy
	{
		T *get(T *current)
		{
			return new T();
		}
	};

	template <typename TData, typename TFind>
	int index_of(TData const &data, TFind const &find)
	{
		return data.index_of(find);
	}

	template <typename TFind>
	int index_of(std::string const &data, TFind const &find)
	{
		return data.find_first_of(find);
	}

	template <typename T>
	T substr(T const &data, int start, int end)
	{
		return data.substr(start, end);
	}

	template <typename T>
	T substr(T const &data, int start)
	{
		return data.substr(start);
	}
}