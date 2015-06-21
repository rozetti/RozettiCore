/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include "../../third_party/RapidXml/rapidxml.hpp"

namespace rz
{
	class dom_document_impl;

	class dom_node_impl
	{
	public:
		enum type {
			node,
			attribute
		};

		friend class dom_node; // hack crz: try to decouple these
		friend class dom_document;

		dom_node_impl();
		dom_node_impl(dom_node_impl const &);
		explicit dom_node_impl(rapidxml::xml_base<> *node);
		explicit dom_node_impl(rapidxml::xml_node<> *node);
		explicit dom_node_impl(rapidxml::xml_attribute<> *node);
		~dom_node_impl();

		std::shared_ptr<dom_node_impl> get_first_child() const;
		std::shared_ptr<dom_node_impl> get_next_sibling() const;
		std::shared_ptr<dom_node_impl> get_first_attribute() const;

		std::string get_name() const;
		std::string get_value() const;

		bool is_valid() const;
		operator bool() { return is_valid(); }

		bool operator==(dom_node_impl const &other) 
		{ 
			return m_rapidxml_node == other.m_rapidxml_node; 
		}

		bool operator!=(dom_node_impl const &other) 
		{ 
			return m_rapidxml_node != other.m_rapidxml_node; 
		}

	protected:
		rapidxml::xml_base<> *m_rapidxml_node;
		type m_type;
	};
}
