#include "tests.h"

#include "object_visitor_policy_tests.h"

int get_handle()
{
	static int h = 0;
	
	return ++h;
}

namespace object_visitor_policy_tests
{
	TEST(ObjectVisitorOperationsTests, test1)
	{
		Thing *t1 = new Thing1();
		Thing *t1a = new Thing2();
		Thing *t2 = new Thing1();
		
		PrintVisitor print_visitor;
		ConstructVisitor construct_visitor;
		
		t1->accept(construct_visitor);
		EXPECT_TRUE(t1->construct_called);
		EXPECT_FALSE(t1->print_called);
		
		EXPECT_FALSE(t1a->construct_called);
		EXPECT_FALSE(t1a->print_called);
		
		EXPECT_FALSE(t2->construct_called);
		EXPECT_FALSE(t2->print_called);
		
		t1->accept(print_visitor);
		EXPECT_TRUE(t1->construct_called);
		EXPECT_TRUE(t1->print_called);
		
		EXPECT_FALSE(t1a->construct_called);
		EXPECT_FALSE(t1a->print_called);
		
		EXPECT_FALSE(t2->construct_called);
		EXPECT_FALSE(t2->print_called);
		
		t2->accept(construct_visitor);
		EXPECT_TRUE(t1->construct_called);
		EXPECT_TRUE(t1->print_called);
		
		EXPECT_FALSE(t1a->construct_called);
		EXPECT_FALSE(t1a->print_called);
		
		EXPECT_TRUE(t2->construct_called);
		EXPECT_FALSE(t2->print_called);
		
		t1a->accept(construct_visitor);
		EXPECT_TRUE(t1->construct_called);
		EXPECT_TRUE(t1->print_called);
		
		EXPECT_TRUE(t1a->construct_called);
		EXPECT_FALSE(t1a->print_called);
		
		EXPECT_TRUE(t2->construct_called);
		EXPECT_FALSE(t2->print_called);
		
		t1a->accept(print_visitor);
		EXPECT_TRUE(t1->construct_called);
		EXPECT_TRUE(t1->print_called);
		
		EXPECT_TRUE(t1a->construct_called);
		EXPECT_TRUE(t1a->print_called);
		
		EXPECT_TRUE(t2->construct_called);
		EXPECT_FALSE(t2->print_called);
		
		t2->accept(print_visitor);
		EXPECT_TRUE(t1->construct_called);
		EXPECT_TRUE(t1->print_called);
		
		EXPECT_TRUE(t1a->construct_called);
		EXPECT_TRUE(t1a->print_called);
		
		EXPECT_TRUE(t2->construct_called);
		EXPECT_TRUE(t2->print_called);
	}
}