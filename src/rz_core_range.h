/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#include <memory>

namespace rz
{
	template <typename T, typename TIter = typename T::iterator>
	class range
	{
	public:
		range(T *obj, TIter (T::*begin_func)(void) const, TIter (T::*end_func)(void) const) :
		m_obj(obj),
		m_begin_func(begin_func),
		m_end_func(end_func)
        { }
		
		range(T *obj, TIter (T::*begin_func)(void) const) :
		m_obj(obj),
		m_begin_func(begin_func),
		m_end_func(&T::end)
        { }
		
		TIter begin() { return (m_obj->*m_begin_func)(); }
		TIter end() { return (m_obj->*m_end_func)(); }
		
	private:
		T *m_obj;
		TIter (T::*m_begin_func)() const;
		TIter (T::*m_end_func)() const;
	};

	template <typename T, typename TIter>
	class range<T const, TIter>
	{
	public:
		range(T const *obj, TIter (T::*begin_func)(void) const, TIter (T::*end_func)(void) const) :
		m_obj(obj),
		m_begin_func(begin_func),
		m_end_func(end_func)
        { }
		
		range(T const *obj, TIter (T::*begin_func)(void) const) :
		m_obj(obj),
		m_begin_func(begin_func),
		m_end_func(&T::end)
        { }
		
		TIter begin() { return (m_obj->*m_begin_func)(); }
		TIter end() { return (m_obj->*m_end_func)(); }
		
	private:
		T const *m_obj;
		TIter (T::*m_begin_func)() const;
		TIter (T::*m_end_func)() const;
	};
	
	template <typename TIter, typename U>
	range<U, TIter> make_range(U &obj, TIter (U::*begin_func)(void) const)
	{
		return range<U, TIter>(&obj, begin_func);
	}

	template <typename TIter, typename U>
	range<U const, TIter> make_range(U const &obj, TIter (U::*begin_func)(void) const)
	{
		return range<U const, TIter>(&obj, begin_func);
	}
	
	template <typename TIter, typename U>
	range<U, TIter> make_range(U *obj, TIter (U::*begin_func)(void) const, TIter (U::*end_func)(void) const)
	{
		return range<U, TIter>(obj, begin_func, end_func);
	}
}