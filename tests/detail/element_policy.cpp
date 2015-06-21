#include "element_policy.h"

namespace VisitorPatternWithContainerOfElements
{
	template <> void VisitorPolicy::visit<element1>(element1 &object)
	{
		object.visit_called = true;
		message = "element1";
	}
	
	template <> void VisitorPolicy::visit<element2>(element2 &object)
	{
		object.visit_called = true;
		message = "element2";
	}
	
	template <> void VisitorPolicy::visit<element3>(element3 &object)
	{
		object.visit_called = true;
		message = "element3";
	}
}