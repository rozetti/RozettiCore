#include "tests.h"

#include <vector>
#include <memory>

#include "detail/element_policy.h"

namespace VisitorPatternWithContainerOfElements
{
	TEST(VisitorPatternWithContainerOfElementsTest, VectorOfElements)
	{
		std::vector<std::shared_ptr<element_base> > elements;
		
		auto e1 = std::make_shared<element1>();
		auto e2 = std::make_shared<element2>();
		auto e3 = std::make_shared<element3>();
		
		elements.push_back(e1);
		elements.push_back(e2);
		elements.push_back(e3);

		for(auto e : elements)
		{
			Visitor v;
			
			EXPECT_STREQ("", v.get_policy().message.c_str());
			EXPECT_FALSE(e->visit_called);
			
			e->accept(v);
			EXPECT_TRUE(e->visit_called);
			EXPECT_STREQ(e->name.c_str(), v.get_policy().message.c_str());
		}
	}
	
}