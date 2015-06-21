/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include <string>
#include <memory>
#include <algorithm>

#include "rz_core_range.h"
#include "rz_core_dom_node.h"
#include "impl/rz_core_dom_node_impl.h"
#include "rz_core_conversion.h"

rz::dom_node::dom_node() :
	m_impl(nullptr)
{
}

rz::dom_node::dom_node(rz::dom_node const &other) :
	m_impl(other.m_impl)
{
}

rz::dom_node::dom_node(std::shared_ptr<rz::dom_node_impl> &other) 
{
	if (other)
	{
		m_impl = other;
	}
	else
	{
		m_impl = nullptr;
	}
}

rz::dom_node::~dom_node()
{
}

rz::dom_node &rz::dom_node::operator=(rz::dom_node const &other)
{
	m_impl = other.m_impl;

	return *this;
}

rz::dom_node rz::dom_node::get_first_child() const
{
    auto node = m_impl->get_first_child();
    
	return rz::dom_node(node);
}

rz::dom_node rz::dom_node::get_first_child(std::string const &name) const
{
    auto f = [&name](rz::dom_node const &node)
    {
        return node.get_name() == name;
    };
    
	rz::dom_node::iterator node = std::find_if(begin_children(), end(), f);
    
	return *node;
}

rz::dom_node rz::dom_node::get_next_sibling() const
{
	if (!*this)
	{
		return rz::dom_node();
	}
	auto sibling = m_impl->get_next_sibling();
	auto node = dom_node(sibling);

	return node;
}

rz::dom_node rz::dom_node::get_first_attribute() const
{
    auto attr = m_impl->get_first_attribute();
    
	return rz::dom_node(attr);
}

rz::dom_node rz::dom_node::get_attribute(std::string const &name) const
{
	rz::dom_node::iterator attr = std::find_if(begin_attributes(), end(), [&name](rz::dom_node const &node)
	{
		return node.get_name() == name;
	});

	return *attr;
}

std::string rz::dom_node::get_name() const
{
	if (!is_valid()) return std::string();

	return std::move(m_impl->get_name());
}

std::string rz::dom_node::get_value() const
{
	if (!is_valid()) return std::string();

	return std::move(m_impl->get_value());
}

int rz::dom_node::get_value_as_int(int default_value) const
{
	if (!is_valid()) return default_value;

	return rz::to_int(get_value(), default_value);
}

float rz::dom_node::get_value_as_float(float default_value) const
{
	if (!is_valid()) return default_value;

	return rz::to_float(get_value(), default_value);
}

double rz::dom_node::get_value_as_double(double default_value) const
{
	if (!is_valid()) return default_value;

	return rz::to_double(get_value(), default_value);
}

bool rz::dom_node::is_valid() const
{
	if (nullptr == m_impl)
	{
		return false;
	}

	return m_impl->is_valid();
}

rz::dom_node::iterator rz::dom_node::begin_attributes() const
{ 
	auto node = get_first_attribute();

	rz::dom_node::iterator it(node); 

	return it;
}

rz::dom_node::iterator rz::dom_node::begin_siblings() const
{ 
	auto sibling = get_next_sibling();

	rz::dom_node::iterator it(sibling); 

	return it;
}

rz::dom_node::iterator rz::dom_node::begin_children() const
{ 
	auto child = get_first_child();

	rz::dom_node::iterator it(child); 

	return it;
}

rz::dom_node::iterator rz::dom_node::end() const
{ 
	rz::dom_node node;
	rz::dom_node::iterator it(node); 

	return it;
}

rz::dom_node::iterator &rz::dom_node::iterator::operator++()
{
	auto sibling = m_node_impl->get_next_sibling();

	if (nullptr != sibling->m_rapidxml_node)
	{
		m_node_impl = sibling;
	}
	else
	{
		m_node_impl = nullptr;
	}

	return *this;
}

rz::dom_node::iterator rz::dom_node::iterator::operator++(int)
{
	auto p = *this;
	++(*this); // todo crz: safety
	return p;
}

rz::dom_node::iterator::iterator() :
	m_node_impl(nullptr)
{
}

rz::dom_node::iterator::iterator(rz::dom_node::iterator const &other)
{
		m_node_impl = other.m_node_impl;
}

rz::dom_node::iterator::iterator(rz::dom_node const &node)
{
	m_node_impl = node.m_impl;;
}

rz::dom_node::iterator::~iterator()
{
}

bool rz::dom_node::iterator::operator!=(iterator const &other) const
{
	return !(*this == other);
}

bool rz::dom_node::iterator::operator==(iterator const &other) const
{
	if (!is_valid())
	{
		return !other.is_valid();
	}

	if (!other.is_valid())
	{
		return false;
	}

	return m_node_impl->m_rapidxml_node == other.m_node_impl->m_rapidxml_node;
}

rz::dom_node rz::dom_node::find(rz::range<rz::dom_node> range, std::string const &key)
{
	for (auto a : range)
	{
		if (a.get_name() == key)
		{
			return a;
		}
	}

	return *(range.end());
}

bool rz::dom_node::iterator::is_valid() const
{
	if (nullptr == m_node_impl) return false;

	return nullptr != m_node_impl->m_rapidxml_node;
}

rz::range<rz::dom_node> rz::dom_children(rz::dom_node &node)
{
	return rz::make_range(node, &rz::dom_node::begin_children);
}

rz::range<rz::dom_node> rz::dom_siblings(rz::dom_node &node)
{
	return rz::make_range(node, &rz::dom_node::begin_siblings);
}

//rz::range<rz::dom_node const> rz::dom_attributes(rz::dom_node const &node)
//{
//	return rz::make_range(node, &rz::dom_node::begin_attributes);
//}
