#pragma once

#pragma warning (disable: 4250)

#include "../../src/rz_core.h"

#include "objects.h"

namespace Test
{
	class ObjectBaseImpl :
		virtual public rz::interfaces::object_base,
		virtual public rz::visitable<VisitorTypeList>
	{
		std::string name;
		int handle;
		
	public:
		ObjectBaseImpl(std::string const &_name) : name(_name) { }
		virtual ~ObjectBaseImpl() { }
		
		virtual std::string const get_name() const { return name; }
		virtual int get_handle() const override { return handle; }
	};

	class ObjectWithPositionImpl :
		public ObjectBaseImpl,
		public interfaces::object_with_position,
		public rz::visitable<VisitorTypeList, ObjectWithPositionImpl>
	{
		double x, y;
	
	public:
		ObjectWithPositionImpl(double _x, double _y) : x(_x), y(_y), ObjectBaseImpl("ObjectWithPositionImpl")	{ }
	
		inline double get_x() const { return x; }
		inline double get_y() const { return y; }
		inline void set_x(double _x) { x = _x; }
		inline void set_y(double _y) { y = _y; }
		
		inline void move(double _x, double _y)
		{
			x = _x;
			y = _y;
		}
	};

	class ObjectWithSizeImpl :
		public ObjectBaseImpl,
		public interfaces::object_with_size,
		public rz::visitable<VisitorTypeList, ObjectWithSizeImpl>
	{
		double w, h;
		
	public:
		ObjectWithSizeImpl(double _w, double _h) : w(_w), h(_h), ObjectBaseImpl("ObjectWithSizeImpl")	{ }
	
		inline double get_w() const { return w; }
		inline double get_h() const { return h; }
		inline void set_w(double _w) { w = _w; }
		inline void set_h(double _h) { h = _h; }
		
		inline void resize(double _w, double _h) { w = _w; h = _h; }
	};

	class ObjectWithBoundingBoxImpl :
		public ObjectBaseImpl,
		public interfaces::object_with_bounding_box,
		public rz::visitable<VisitorTypeList, ObjectWithBoundingBoxImpl>
	{
		::rz::bounding_box box;
		
	public:
		ObjectWithBoundingBoxImpl(::rz::bounding_box const &_box) :
			box(_box),
			ObjectBaseImpl("ObjectWithBoundingBoxImpl")
	{ }
	
		inline rz::bounding_box const &get_bounding_box() const { return box; }
		inline void set_bounding_box(::rz::bounding_box const &_box) { box = _box; }
		
		inline void grow(float amount) { box = rz::bounding_box(box.min() - amount, box.max() + amount); }
	};
}
