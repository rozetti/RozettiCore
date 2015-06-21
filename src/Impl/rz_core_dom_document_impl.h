/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include "../../third_party/RapidXml/rapidxml.hpp"

#include <memory>
#include <vector>

#include "rz_core_dom_node_impl.h"

namespace rz
{
	class dom_document_impl : public dom_node_impl
	{
	public:
		dom_document_impl();
		~dom_document_impl();

		bool parse(std::string const &source);

	private:
		std::unique_ptr<rapidxml::xml_document<char> > m_document;

		std::vector<char> m_data;
	};
}