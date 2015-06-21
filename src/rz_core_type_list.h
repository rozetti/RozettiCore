/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#pragma once

// crz: this stuff is very difficult to understand

namespace rz // type_list::type_list
{
	namespace type_list
	{
		template <class H, class T>
		class type_list
		{
		public:
			typedef H head;
			typedef T tail;
		};
		
		class terminator_type {};
	}
}

namespace rz // type_list::length
{
	namespace type_list
	{
		template <class T> struct length;
		
		template <>
		struct length<terminator_type>
		{
			enum { value = 0 };
		};
		
		template <class H, class T>
		struct length<type_list<H, T>>
		{
			enum { value = 1 + length<T>::value };
		};
	}
}

namespace rz // type_list::at
{
	namespace type_list
	{
		template <class T, int I> struct at;
		
		template <class H, class T>
		struct at<type_list<H, T>, 0>
		{
			typedef H type;
		};
		
		template <class H, class T, int N>
		struct at<type_list<H, T>, N>
		{
			typedef typename at<T, N-1>::type type;
		};
	}
}

namespace rz // type_list::expander
{
	namespace type_list
	{
		template <class type_list, template <typename T> class TTemplate> struct expander;
		
		template <class H, template <typename P> class TTemplate>
		struct expander<type_list<H, terminator_type>, TTemplate> :
			public TTemplate<H>
		{
		};
		
		template <class H, class T, template <typename P> class TTemplate>
		struct expander<type_list<H, T>, TTemplate> :
			public TTemplate<H>, public expander<T, TTemplate>
		{
			using TTemplate<T>::number; // todo crz: make this general
		};
	}
}

namespace rz
{
	namespace type_list
	{
		template <class T1> struct type_list_1
		{
			typedef type_list<T1, terminator_type> type_list;
		};
		
		template <class T1, class T2> struct type_list_2
		{
			typedef type_list<T1, typename type_list_1<T2>::type_list > type_list;
		};
		
		template <class T1, class T2, class T3> struct type_list_3
		{
			typedef type_list<T1, typename type_list_2<T2, T3>::type_list > type_list;
		};
		
		template <class T1, class T2, class T3, class T4> struct type_list_4
		{
			typedef type_list<T1, typename type_list_3<T2, T3, T4>::type_list > type_list;
		};
		
		template <class T1, class T2, class T3, class T4, class T5> struct type_list_5
		{
			typedef type_list<T1, typename type_list_4<T2, T3, T4, T5>::type_list > type_list;
		};
		
		template <class T1, class T2, class T3, class T4, class T5, class T6> struct type_list_6
		{
			typedef type_list<T1, typename type_list_5<T2, T3, T4, T5, T6>::type_list > type_list;
		};
		
		template <class T1, class T2, class T3, class T4, class T5, class T6, class T7> struct type_list_7
		{
			typedef type_list<T1, typename type_list_6<T2, T3, T4, T5, T6, T7>::type_list > type_list;
		};
		
		template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8> struct type_list_8
		{
			typedef type_list<T1, typename type_list_7<T2, T3, T4, T5, T6, T7, T8>::type_list > type_list;
		};
		
		template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9> struct type_list_9
		{
			typedef type_list<T1, typename type_list_8<T2, T3, T4, T5, T6, T7, T8, T9>::type_list > type_list;
		};
		
		template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10> struct type_list_10
		{
			typedef type_list<T1, typename type_list_9<T2, T3, T4, T5, T6, T7, T8, T9, T10>::type_list > type_list;
		};
	}
}
#define rz_T1(t1) rz::type_list::type_list<t1, rz::type_list::terminator_type>
#define rz_T2(t1, t2) rz::type_list::type_list<t1, rz_TL1(t2)>
#define rz_T3(t1, t2, t3) rz::type_list::type_list<t1, rz_TL2(t2, t3)>
#define rz_T4(t1, t2, t3, t4) rz::type_list::type_list<t1, rz_TL3(t2, t3, t4)>
#define rz_T5(t1, t2, t3, t4, t5) rz::type_list::type_list<t1, rz_TL4(t2, t3, t4, t5)>

#define rz_TL1(t1) rz::type_list::type_list_1<t1>::type_list
#define rz_TL2(t1, t2) rz::type_list::type_list_2<t1, t2>::type_list
#define rz_TL3(t1, t2, t3) rz::type_list::type_list_3<t1, t2, t3>::type_list
#define rz_TL4(t1, t2, t3, t4) rz::type_list::type_list_4<t1, t2, t3, t4>::type_list
#define rz_TL5(t1, t2, t3, t4, t5) rz::type_list::type_list_5<t1, t2, t3, t4, t5>::type_list

#define rz_TL10(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10) rz::type_list::type_list_10<t1, t2, t3, t4, t5, t6, t7, t8, t9, t10>::type_list