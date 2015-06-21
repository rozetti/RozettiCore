/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include <string>
#include <iterator>
#include <memory>

#include "rz_core_range.h"

namespace rz
{
	class dom_node_impl;

	class dom_node
	{
	public:
		class iterator : public ::std::iterator<::std::forward_iterator_tag, dom_node>
		{
		public:
			iterator();
			explicit iterator(dom_node const &node);
			iterator(iterator const &other);
			~iterator();

			iterator &operator++();
			iterator operator++(int);

			dom_node operator*()
			{
				return dom_node(m_node_impl);
			}

			bool operator!=(iterator const &other) const;
			bool operator==(iterator const &other) const;

			bool is_valid() const;

		private:
            std::shared_ptr<dom_node_impl> m_node_impl;
		};

		dom_node();
		dom_node(dom_node const &);
		explicit dom_node(std::shared_ptr<dom_node_impl> &other);
		~dom_node();

		dom_node &operator=(dom_node const &);
		operator bool() const { return is_valid(); }

		bool is_valid() const;

		dom_node get_first_child() const;
		dom_node get_first_child(std::string const &name) const;
		dom_node get_next_sibling() const;
		dom_node get_first_attribute() const;
		dom_node get_attribute(std::string const &name) const;

		std::string get_name() const;
		std::string get_value() const;
		int get_value_as_int(int default_value) const;
		float get_value_as_float(float default_value) const;
		double get_value_as_double(double default_value) const;

		void set_impl(dom_node_impl *impl);
		dom_node_impl *get_impl() const;

		iterator begin_children() const;
		iterator begin_siblings() const;
		iterator begin_attributes() const;
		iterator begin() const { return begin_children(); }

		iterator end() const;

		static dom_node find(rz::range<dom_node> range, std::string const &key);

	protected:
        std::shared_ptr<dom_node_impl> m_impl;
	};

	rz::range<rz::dom_node> dom_children(rz::dom_node &node);
	rz::range<rz::dom_node> dom_siblings(rz::dom_node &node);
	
	template <typename T>
	rz::range<T> dom_attributes(T &node)
	{
		return rz::make_range(node, &rz::dom_node::begin_attributes);
	}
}
