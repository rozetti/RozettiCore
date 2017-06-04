/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

namespace rz
{
	namespace detail
	{
		template <typename T>
		class rectangle
		{
		public:
			T x;
			T y;
			T width;
			T height;

			rectangle() : x(0), y(0), width(0), height(0) {}
			rectangle(T _x, T _y, T _w, T _h) : x(_x), y(_y), width(_w), height(_h) {}
		};
	}

	using irectangle = detail::rectangle<int>;

	class rectangle
	{
	public:
		float x;
		float y;
		float width;
		float height;
		
		rz::rectangle();
		rz::rectangle(float x, float y, float width, float height);
		rz::rectangle(rz::rectangle const &);

		float right() const;
		float bottom() const;

		bool contains(rz::rectangle const &other) const;
		bool contains(float x, float y) const;
		bool equals(rz::rectangle const &other) const;
		bool intersects(rz::rectangle const &inRect) const;

		bool is_empty() const;

		rz::rectangle union_with(rz::rectangle const &other) const;
		rz::rectangle intersection_with(rz::rectangle const &other) const;
	};
}
