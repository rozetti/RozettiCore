/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "../../third_party/RapidXml/rapidxml.hpp"

#include "rz_core_dom_document_impl.h"

rz::dom_document_impl::dom_document_impl() :
	m_document(new rapidxml::xml_document<char>())
{
}

rz::dom_document_impl::~dom_document_impl()
{
}

bool rz::dom_document_impl::parse(std::string const &source)
{
	if (source.empty())
	{
		return false;
	}

	m_data.reserve(source.size() + 1);
	
	m_data.assign(source.begin(), source.end());
	m_data.push_back(0);

	m_document->parse<rapidxml::parse_trim_whitespace>(&m_data[0]);
	m_rapidxml_node = m_document->first_node(); // crz: bit hacky

	return true;
}
