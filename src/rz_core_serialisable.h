/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include <string>

namespace rz
{
	template <class TSerialiseOutput = std::string, class TDeserialiseInput = std::string>
	struct serialisable
	{
		typedef TSerialiseOutput serialise_output_type;
		typedef TDeserialiseInput deseralise_input_type;
		
		virtual TSerialiseOutput serialise() const = 0;
		virtual bool deserialise(TDeserialiseInput &serialised) = 0;
	};
}

