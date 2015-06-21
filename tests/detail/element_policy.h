#pragma once

#include "../../src/rz_core.h"

#include <string>

#define ELEMENT(ELEMENT) \
struct ELEMENT : public element_base, public rz::visitable<VisitorTypeList, ELEMENT> \
{ \
ELEMENT() : element_base("" #ELEMENT "") {} \
};

namespace VisitorPatternWithContainerOfElements
{
	struct element1;
	struct element2;
	struct element3;
	struct VisitorPolicy;

	typedef rz::type_list::type_list_3<element1, element2, element3>::type_list ObjectTypeList;
	typedef rz::visitor<ObjectTypeList, VisitorPolicy> Visitor;
	typedef rz::type_list::type_list_1<Visitor>::type_list VisitorTypeList;

	struct element_base : virtual public rz::visitable<VisitorTypeList>
	{
		element_base(std::string const &_name) : name(_name), visit_called(false) { }
		virtual ~element_base() { }
		std::string name;
		bool visit_called;
	};

	ELEMENT(element1)
	ELEMENT(element2)
	ELEMENT(element3)

	struct VisitorPolicy
	{
		VisitorPolicy() : message("") { }
		template <class TObject> void visit(TObject &object);
		
		std::string message;
	};
}
