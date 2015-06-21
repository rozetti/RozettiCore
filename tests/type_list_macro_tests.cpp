#include "tests.h"

#define THING(name, n) struct name { enum { value = n }; int get() { return n; } };

THING(Thing1, 1)
THING(Thing2, 2)
THING(Thing3, 3)
THING(Thing4, 4)

// yagni crz: there are probably deprecated by the template versions
typedef rz_T1(Thing1) one_type;
typedef rz_T2(Thing1, Thing2) two_types;
typedef rz_T3(Thing1, Thing2, Thing3) three_types;
typedef rz_T4(Thing1, Thing2, Thing3, Thing4) four_types;

TEST(TypeListMacroTest, TypeMacros)
{
	EXPECT_EQ(1, one_type::head().get());
	
	EXPECT_EQ(1, two_types::head().get());
	EXPECT_EQ(2, two_types::tail::head().get());
	
	EXPECT_EQ(1, three_types::head().get());
	EXPECT_EQ(2, three_types::tail::head().get());
	EXPECT_EQ(3, three_types::tail::tail::head().get());
	
	EXPECT_EQ(1, four_types::head().get());
	EXPECT_EQ(2, four_types::tail::head().get());
	EXPECT_EQ(3, four_types::tail::tail::head().get());
	EXPECT_EQ(4, four_types::tail::tail::tail::head().get());
}

// crz: these are preferable
typedef rz_TL1(Thing1) one_type_list;
typedef rz_TL2(Thing1, Thing2) two_types_list;
typedef rz_TL3(Thing1, Thing2, Thing3) three_types_list;
typedef rz_TL4(Thing1, Thing2, Thing3, Thing4) four_types_list;

TEST(TypeListMacroTest, TypeListMacros)
{
	EXPECT_EQ(1, one_type_list::head().get());
	
	EXPECT_EQ(1, two_types_list::head().get());
	EXPECT_EQ(2, two_types_list::tail::head().get());
	
	EXPECT_EQ(1, three_types_list::head().get());
	EXPECT_EQ(2, three_types_list::tail::head().get());
	EXPECT_EQ(3, three_types_list::tail::tail::head().get());
	
	EXPECT_EQ(1, four_types_list::head().get());
	EXPECT_EQ(2, four_types_list::tail::head().get());
	EXPECT_EQ(3, four_types_list::tail::tail::head().get());
	EXPECT_EQ(4, four_types_list::tail::tail::tail::head().get());
}

TEST(TypeListMacroTest, Length)
{
	EXPECT_EQ(1, rz::type_list::length<one_type>::value);
	EXPECT_EQ(2, rz::type_list::length<two_types>::value);
	EXPECT_EQ(3, rz::type_list::length<three_types>::value);
	EXPECT_EQ(4, rz::type_list::length<four_types>::value);

	EXPECT_EQ(1, rz::type_list::length<one_type_list>::value);
	EXPECT_EQ(2, rz::type_list::length<two_types_list>::value);
	EXPECT_EQ(3, rz::type_list::length<three_types_list>::value);
	EXPECT_EQ(4, rz::type_list::length<four_types_list>::value);
}

