#include "../object_visitor_policy_tests.h"

#include <iostream>

namespace object_visitor_policy_tests
{
	template <>	void ObjectVisitorOperations<Thing1>::print(Thing1 &object)
	{
		std::cout << "ObjectVisitorOperations::print<Thing1>()" << std::endl;
		
		object.print_called = true;
	}
	
	template <> void ObjectVisitorOperations<Thing1>::construct(Thing1 &object)
	{
		std::cout << "ObjectVisitorOperations::construct<Thing1>()" << std::endl;
		
		object.construct_called = true;
	}
	
	template <> void ObjectVisitorOperations<Thing2>::print(Thing2 &object)
	{
		std::cout << "ObjectVisitorOperations::print<Thing2>()" << std::endl;
		
		object.print_called = true;
	}
	
	template <> void ObjectVisitorOperations<Thing2>::construct(Thing2 &object)
	{
		std::cout << "ObjectVisitorOperations::construct<Thing2>()" << std::endl;
		
		object.construct_called = true;
	}
}