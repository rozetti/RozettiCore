#pragma once

#include "../../src/rz_core.h"

namespace Test
{
	namespace interfaces
	{
		class object_base : virtual public rz::interfaces::object_base
		{
		};
		
		class object_with_position : public object_base
		{
		public:
			virtual double get_x() const = 0;
			virtual void set_x(double _x) = 0;
			virtual double get_y() const = 0;
			virtual void set_y(double _y) = 0;
			
			virtual void move(double x, double y) = 0;
		};
		
		class object_with_size : public object_base
		{
		public:
			virtual double get_w() const = 0;
			virtual void set_w(double _w) = 0;
			virtual double get_h() const = 0;
			virtual void set_h(double _h) = 0;
			
			virtual void resize(double w, double h) = 0;
		};
		
		class object_with_bounding_box : public object_base
		{
		public:
			typedef rz::bounding_box bounding_box_type;
			
			virtual bounding_box_type const &get_bounding_box() const = 0;
			virtual void set_bounding_box(bounding_box_type const &) = 0;
			
			virtual void grow(float factor) = 0;
		};
	}

	typedef rz::type_list::type_list_3
	<
	interfaces::object_with_position,
	interfaces::object_with_size,
	interfaces::object_with_bounding_box
	>::type_list ObjectTypeList;

	typedef rz::type_list::type_list_5
	<
	rz::visitor<ObjectTypeList, rz::lua_scriptable_object_visitor_print_policy>,
	rz::visitor<ObjectTypeList, rz::lua_scriptable_object_visitor_construct_policy>,
	rz::visitor<ObjectTypeList, rz::lua_scriptable_object_visitor_destruct_policy>,
	rz::visitor<ObjectTypeList, rz::lua_scriptable_object_visitor_upload_policy>,
	rz::visitor<ObjectTypeList, rz::lua_scriptable_object_visitor_download_policy>
	>::type_list VisitorTypeList;
}

