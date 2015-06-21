/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include <sstream>
#include <iostream>

#include "rz_core_dom_document.h"
#include "rz_core_dom_node.h"
#include "impl/rz_core_dom_document_impl.h"

rz::dom_document::dom_document() :
	m_impl(nullptr) 
{
	m_impl = new dom_document_impl();
}

rz::dom_document::~dom_document()
{
	if (nullptr != m_impl)
	{
		delete m_impl;
		m_impl = (rz::dom_document_impl *)nullptr;
	}
}

bool rz::dom_document::parse(std::string const &xml)
{
	std::stringstream ss(xml);

	auto b = true;
	
	try
	{
		b = m_impl->parse(xml);
	}
	catch (...)
	{
		b = false;
	}

	if (b)
	{
		std::shared_ptr<rz::dom_node_impl> impl = std::make_shared<rz::dom_node_impl>((rz::dom_node_impl)m_impl->m_rapidxml_node);

		rz::dom_node::m_impl = impl;
	}

	return b;
}
