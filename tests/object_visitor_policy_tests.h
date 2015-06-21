#pragma once

#include "../src/rz_core.h"

int get_handle();

namespace object_visitor_policy_tests
{
	template <class TObject> struct ObjectVisitorOperations
	{
		static void construct(TObject &object);
		static void print(TObject &object);
	};
	
	struct VisitorPrintPolicy
	{
		template <class TObject> void visit(TObject &object)
		{
			ObjectVisitorOperations<TObject>::print(object);
		}
	};
	
	struct VisitorConstructPolicy
	{
		template <class TObject> void visit(TObject &object)
		{
			ObjectVisitorOperations<TObject>::construct(object);
		}
	};
	
	typedef rz::type_list::type_list_2
	<
	struct Thing1,
	struct Thing2
	>::type_list ObjectTypes;
	
	typedef rz::visitor<ObjectTypes, VisitorPrintPolicy> PrintVisitor;
	typedef rz::visitor<ObjectTypes, VisitorConstructPolicy> ConstructVisitor;
	
	typedef rz::type_list::type_list_2
	<
	PrintVisitor,
	ConstructVisitor
	>::type_list VisitorTypes;
	
	struct Thing :
	public virtual rz::interfaces::object_base,
	public virtual rz::visitable<VisitorTypes>
	{
		Thing() : print_called(false), construct_called(false) { }
		virtual int get_handle() const { return ::get_handle(); }
		
		bool construct_called;
		bool print_called;
	};
	
	struct Thing1 :	public Thing, public rz::visitable<VisitorTypes, Thing1>
	{
		virtual std::string const get_name() const { return std::string("Thing1"); }
	};
	
	struct Thing2 : public Thing, public rz::visitable<VisitorTypes, Thing2>
	{
		virtual std::string const get_name() const { return std::string("Thing2"); }
	};
}
