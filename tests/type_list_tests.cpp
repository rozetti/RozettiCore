#include "tests.h"

#define THING(NAME, N) struct NAME { enum { value = N }; int get() { return value; } };

THING(Thing1, 1)
THING(Thing2, 2)
THING(Thing3, 3)
THING(Thing4, 4)
THING(Thing5, 5)
THING(Thing6, 6)
THING(Thing7, 7)
THING(Thing8, 8)
THING(Thing9, 9)
THING(Thing10, 10)

typedef rz::type_list::type_list_1<Thing1>::type_list one_type;
typedef rz::type_list::type_list_2<Thing1, Thing2>::type_list two_types;
typedef rz::type_list::type_list_3<Thing1, Thing2, Thing3>::type_list three_types;
typedef rz::type_list::type_list_4<Thing1, Thing2, Thing3, Thing4>::type_list four_types;

typedef rz_TL1(Thing1) one_type;
typedef rz_TL2(Thing1, Thing2) two_types;
typedef rz_TL3(Thing1, Thing2, Thing3) three_types;
typedef rz_TL4(Thing1, Thing2, Thing3, Thing4) four_types;

typedef rz_TL10(
	Thing1,
	Thing2,
	Thing3,
	Thing4,
	Thing5,
	Thing6,
	Thing7,
	Thing8,
	Thing9,
	Thing10
) ten_types;

TEST(TypeListTest, Templates)
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

	EXPECT_EQ(1, ten_types::head().get());
	EXPECT_EQ(2, ten_types::tail::head().get());
	EXPECT_EQ(3, ten_types::tail::tail::head().get());
	EXPECT_EQ(4, ten_types::tail::tail::tail::head().get());
	EXPECT_EQ(5, ten_types::tail::tail::tail::tail::head().get());
	EXPECT_EQ(6, ten_types::tail::tail::tail::tail::tail::head().get());
	EXPECT_EQ(7, ten_types::tail::tail::tail::tail::tail::tail::head().get());
	EXPECT_EQ(8, ten_types::tail::tail::tail::tail::tail::tail::tail::head().get());
	EXPECT_EQ(9, ten_types::tail::tail::tail::tail::tail::tail::tail::tail::head().get());
	EXPECT_EQ(10, ten_types::tail::tail::tail::tail::tail::tail::tail::tail::tail::head().get());
}

TEST(TypeListTest, Length)
{
	EXPECT_EQ(1, rz::type_list::length<one_type>::value);
	EXPECT_EQ(2, rz::type_list::length<two_types>::value);
	EXPECT_EQ(3, rz::type_list::length<three_types>::value);
	EXPECT_EQ(4, rz::type_list::length<four_types>::value);

	EXPECT_EQ(10, rz::type_list::length<ten_types>::value);
}

TEST(TypeListTest, At)
{
	int n = 0;
	
	n = rz::type_list::at<one_type, 0>::type::value;
	EXPECT_EQ(1, n);

	n = rz::type_list::at<two_types, 0>::type::value;
	EXPECT_EQ(1, n);
	n = rz::type_list::at<two_types, 1>::type::value;
	EXPECT_EQ(2, n);

	n = rz::type_list::at<three_types, 0>::type::value;
	EXPECT_EQ(1, n);
	n = rz::type_list::at<three_types, 1>::type::value;
	EXPECT_EQ(2, n);
	n = rz::type_list::at<three_types, 2>::type::value;
	EXPECT_EQ(3, n);

	typedef rz::type_list::at<ten_types, 7>::type TSeven;
	EXPECT_EQ(8, TSeven::value);
	typedef rz::type_list::at<ten_types, 9>::type TTen;
	EXPECT_EQ(10, TTen::value);
}
