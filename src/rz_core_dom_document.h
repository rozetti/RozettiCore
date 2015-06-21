/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include <string>

#include "rz_core_dom_node.h"

namespace rz
{
	class dom_document_impl;

	class dom_document : public dom_node
	{
	public:
		dom_document();
		~dom_document();

		bool parse(std::string const &source);

	protected:
		dom_document_impl *m_impl;
	};
}