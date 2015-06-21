/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

// hack crz

#include <string>
#include <cstring>

namespace rz
{
	template <typename T1>
	static std::string printf(char const *format, T1 t1)
	{
		char buff[100];
#ifdef WIN32
		sprintf_s(buff, sizeof(buff) - 1, format, t1); // too crz: do we need the -1 ?
#else
		sprintf(buff, format, t1);
#endif
		return std::string(buff);
	}

	template <typename T1, typename T2>
	static std::string printf(char const *format, T1 t1, T2 t2)
	{
		char buff[100];
#ifdef WIN32
		sprintf_s(buff, sizeof(buff) - 1, format, t1, t2);
#else
		sprintf(buff, format, t1, t2);
#endif
		return std::string(buff);
	}

	template <typename T1, typename T2, typename T3>
	static std::string printf(char const *format, T1 p1, T2 p2, T3 p3)
	{
		char buff[100];
#ifdef WIN32
		sprintf_s(buff, sizeof(buff) - 1, format, p1, p2, p3);
#else
		sprintf(buff, format, p1, p2, p3);
#endif
		return std::string(buff);
	}
}