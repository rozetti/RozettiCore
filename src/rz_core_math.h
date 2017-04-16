#pragma once

namespace rz
{
	template <typename T> // todo crz: test this
	T next_power_of_two(T n)
	{
		T r = 1;

		while (r < n)
		{
			r <<= 1;
		}

		return r;
	}
}
