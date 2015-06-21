/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

#pragma warning (disable: 4250)

#include "rz_core_type_list.h"

namespace rz
{
	template <class TTypeList, class TVisitPolicy = void> class visitor;
	
	template <class H, class T, class TVisitPolicy>
	class visitor<type_list::type_list<H, T>, TVisitPolicy> : public visitor<T, TVisitPolicy>
	{
		typedef visitor<T, TVisitPolicy> base;

	public:
		using base::visit;
		using base::get_policy;
		
		visitor() : visitor<T, TVisitPolicy>() { }
		template <class TState> explicit visitor(TState *state) : visitor<T, TVisitPolicy>(state) { }

		virtual void visit(H &object) { base::get_policy().visit(object); }
	};
	
	template <class H, class TVisitPolicy>
	class visitor<type_list::type_list<H, type_list::terminator_type>, TVisitPolicy>
	{
	public:
		visitor() : m_policy() { }
		template <class TState> explicit visitor(TState *state) : m_policy(state) { }

		virtual void visit(H &object) { m_policy.visit(object); }

		TVisitPolicy &get_policy() { return m_policy; }
		
	private:
		TVisitPolicy m_policy;
	};
	
	template <class H, class T>
	class visitor<type_list::type_list<H, T>, void> : public visitor<T, void>
	{
	public:
		using visitor<T>::visit;
		virtual void visit(H &object) = 0;
	};
	
	template <class H>
	class visitor<type_list::type_list<H, type_list::terminator_type>, void>
	{
	public:
		virtual void visit(H &object) = 0;
	};
}

namespace rz
{
	template <class TVisitorList, class TCRTP = void> struct visitable;
	
	template <class H>
	struct visitable<typename type_list::type_list<H, type_list::terminator_type>, void>
	{
		virtual void accept(H &visitor) = 0;
	};
	
	template <class H, class T>
	struct visitable<type_list::type_list<H, T>, void> : virtual public visitable<T>
	{
		using visitable<T, void>::accept;
		virtual void accept(H &visitor) = 0;
	};

	template <class H, class TCRTP>
	struct visitable<typename type_list::type_list<H, type_list::terminator_type>, TCRTP> :
		virtual public visitable<typename type_list::type_list<H, type_list::terminator_type>, void>
	{
		using visitable<typename type_list::type_list<H, type_list::terminator_type>, void>::accept;
		
		virtual void accept(H &visitor)
		{
			visitor.visit(*static_cast<TCRTP *>(this));
		}
	};
	
	template <class H, class T, class TCRTP>
	struct visitable<typename type_list::type_list<H, T>, TCRTP> : virtual public visitable<type_list::type_list<H, T>, void>, public visitable<T, TCRTP>
	{
		using visitable<type_list::type_list<H, T>, void>::accept;
		
		virtual void accept(H &visitor)
		{
			visitor.visit(*static_cast<TCRTP *>(this));
		}
	};
}
