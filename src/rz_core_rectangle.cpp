/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core.h"

rz::rectangle::rectangle() :
	x(0), y(0), width(0), height(0)
{
}

rz::rectangle::rectangle(float x, float y, float width, float height) :
	x(x), y(y), width(width), height(height)
{
}

rz::rectangle::rectangle(rz::rectangle const &other) :
	x(other.x), y(other.y), width(other.width), height(other.height)
{
}

// todo crz: inline these
float rz::rectangle::right() const
{
	return x + width;
}

float rz::rectangle::bottom() const
{
	return y + height;
}

bool rz::rectangle::is_empty() const
{
	if (width <= ONE_FLT_EPSILON || height <= ONE_FLT_EPSILON)
	{
		return true;
	}

	return false;
}

bool rz::rectangle::equals(rz::rectangle const &other) const
{
	if (x == other.x && y == other.y && width == other.width && height == other.height)
	{
		return true;
	}

	return false;
}

rz::rectangle rz::rectangle::union_with(rz::rectangle const &other) const
{
	rz::rectangle r;

	if (other.is_empty() || is_empty())
	{
		return r;
	}

	r.x = (x < other.x) ? x : other.x;
	r.y = (y < other.y) ? y : other.y;

	r.width = ((right() > other.right()) ? right() : other.right()) - r.x;
	r.height = ((bottom() > other.bottom()) ? bottom() : other.bottom()) - r.y;

	return r;
}

rz::rectangle rz::rectangle::intersection_with(rz::rectangle const &other) const
{
	rz::rectangle r;

	r.x = rz::max(x, other.x);
	r.y = rz::max(y, other.y);
	r.width = rz::min(right(), other.right()) - r.x;
	r.height = rz::min(bottom(), other.bottom()) - r.y;

	// todo crz: refactor
	if (r.width <= ONE_FLT_EPSILON || r.height <= ONE_FLT_EPSILON)
	{
		r.width = r.height = 0.0f;
	}
	
	return r;
}

bool rz::rectangle::contains(float x, float y) const
{
	return (x >= this->x && y >= this->y && x < right() && y < bottom());
}

bool rz::rectangle::contains(rz::rectangle const &other) const
{
	return 
		other.x >= x &&
		other.y >= y &&
		right() >= other.right() &&
		bottom() >= other.bottom();
}

bool rz::rectangle::intersects(rz::rectangle const &other) const
{
	return !intersection_with(other).is_empty();
}
