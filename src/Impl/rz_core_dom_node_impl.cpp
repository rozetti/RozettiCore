/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "../../third_party/RapidXml/rapidxml.hpp"

#include <memory>
#include <string>
#include "rz_core_dom_node_impl.h"

rz::dom_node_impl::dom_node_impl() :
	m_rapidxml_node(nullptr),
	m_type(type::node)
{
}

rz::dom_node_impl::dom_node_impl(rapidxml::xml_base<> *node) :
	m_rapidxml_node(node),
	m_type(type::node)
{
}

rz::dom_node_impl::dom_node_impl(rapidxml::xml_node<> *node) :
	m_rapidxml_node(node),
	m_type(type::node)
{
}

rz::dom_node_impl::dom_node_impl(rapidxml::xml_attribute<> *node) :
	m_rapidxml_node(node),
	m_type(type::attribute)
{
}

rz::dom_node_impl::dom_node_impl(dom_node_impl const &other) :
	m_rapidxml_node(other.m_rapidxml_node),
	m_type(other.m_type)
{
}

rz::dom_node_impl::~dom_node_impl()
{
}

std::shared_ptr<rz::dom_node_impl> rz::dom_node_impl::get_first_child() const
{
	if (m_type == type::node)
	{
		auto node = static_cast<rapidxml::xml_node<> *>(m_rapidxml_node);

		return std::make_shared<rz::dom_node_impl>(node->first_node());
	}

	return nullptr; // notest crz
}

std::shared_ptr<rz::dom_node_impl> rz::dom_node_impl::get_next_sibling() const
{
	if (m_type == type::node)
	{
		auto node = static_cast<rapidxml::xml_node<> *>(m_rapidxml_node);

		auto next = node->next_sibling();

		return std::make_shared<rz::dom_node_impl>(next);
	}

	if (m_type == type::attribute)
	{
		auto node = static_cast<rapidxml::xml_attribute<> *>(m_rapidxml_node);

		return std::make_shared<rz::dom_node_impl>(node->next_attribute());
	}

	return nullptr; // notest crz
}

std::shared_ptr<rz::dom_node_impl> rz::dom_node_impl::get_first_attribute() const
{
	if (nullptr == m_rapidxml_node)
	{
        // crz: handles the case of no attrs on the node
        return nullptr; // notest crz
	}

	if (m_type == type::node) // crz: (finding attributes on a node, not attributes on an attribute)
	{
		auto node = static_cast<rapidxml::xml_node<> *>(m_rapidxml_node);

		return std::make_shared<rz::dom_node_impl>(node->first_attribute());
	}

	return nullptr; // notest crz
}

std::string rz::dom_node_impl::get_name() const
{
	auto p = m_rapidxml_node->name();

	return std::move(std::string(p));
}

std::string rz::dom_node_impl::get_value() const
{
	return std::move(std::string(m_rapidxml_node->value()));
}

bool rz::dom_node_impl::is_valid() const
{
	auto valid = nullptr != m_rapidxml_node;

	return valid;
}