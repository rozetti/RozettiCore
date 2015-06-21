#include "tests.h"

#include <vector>
#include <iostream>
#include <sstream>

typedef rz::type_list::type_list_4
<
	struct element1,
	struct element2,
	struct element3,
	struct element4
>::type_list Types;

struct VisitorPolicy1
{
	template <class TObject>
	void visit(TObject &object)
	{
		object.visit_called = true;
		
		std::stringstream ss;
		ss << "Visiting " << object.name << " with Policy 1";
		message = ss.str();
		
		std::cout << message << std::endl;
	}
	
	std::string message;
};

struct VisitorPolicy2
{
	template <class TObject>
	void visit(TObject &object)
	{
		object.visit_called = true;

		std::stringstream ss;
		ss << "Visiting " << object.name << " with Policy 2";
		message = ss.str();
		
		std::cout << message << std::endl;
	}

	std::string message;
};

typedef rz::visitor<Types, VisitorPolicy1> visitor1;
typedef rz::visitor<Types, VisitorPolicy2> visitor2;

typedef rz::type_list::type_list_2<visitor1, visitor2>::type_list VisitorTypeList;

#define ELEMENT(ELEMENT) \
struct ELEMENT : public rz::visitable<VisitorTypeList, ELEMENT> \
{ \
	ELEMENT() : visit_called(false), name("" #ELEMENT "") {} \
	bool visit_called; \
	std::string name; \
};

ELEMENT(element1)
ELEMENT(element2)
ELEMENT(element3)
ELEMENT(element4)

TEST(VisitorPatternTest, ElementAcceptsVisitorWithPolicy1)
{
	element1 e1;
	element2 e2;
	element3 e3;
	element4 e4;
	
	EXPECT_FALSE(e1.visit_called);
	EXPECT_FALSE(e2.visit_called);
	EXPECT_FALSE(e3.visit_called);
	EXPECT_FALSE(e4.visit_called);

	visitor1 v;
	
	e1.accept(v);
	EXPECT_TRUE(e1.visit_called);
	EXPECT_STREQ("Visiting element1 with Policy 1", v.get_policy().message.c_str());
	
	e2.accept(v);
	EXPECT_TRUE(e2.visit_called);
	EXPECT_STREQ("Visiting element2 with Policy 1", v.get_policy().message.c_str());

	e3.accept(v);
	EXPECT_TRUE(e3.visit_called);
	EXPECT_STREQ("Visiting element3 with Policy 1", v.get_policy().message.c_str());
	
	e4.accept(v);
	EXPECT_TRUE(e4.visit_called);
	EXPECT_STREQ("Visiting element4 with Policy 1", v.get_policy().message.c_str());
}

TEST(VisitorPatternTest, ElementAcceptsVisitorWithPolicy2)
{
	element1 e1;
	element2 e2;
	element3 e3;
	element4 e4;
	
	visitor2 v;
	
	e1.accept(v);
	EXPECT_TRUE(e1.visit_called);
	EXPECT_STREQ("Visiting element1 with Policy 2", v.get_policy().message.c_str());
	
	e2.accept(v);
	EXPECT_TRUE(e2.visit_called);
	EXPECT_STREQ("Visiting element2 with Policy 2", v.get_policy().message.c_str());
	
	e3.accept(v);
	EXPECT_TRUE(e3.visit_called);
	EXPECT_STREQ("Visiting element3 with Policy 2", v.get_policy().message.c_str());
	
	e4.accept(v);
	EXPECT_TRUE(e4.visit_called);
	EXPECT_STREQ("Visiting element4 with Policy 2", v.get_policy().message.c_str());
}

