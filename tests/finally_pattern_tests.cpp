#include "tests.h"

TEST(FinallyPatternTest, FinalBlockIsCalled)
{
	int n = 0;
	
	{
		rz::finally f([&n]{
			n = 1;
		});
		
		n = 2;
	}
	
	EXPECT_EQ(1, n);
}

class FinallyPatternTests : public ::testing::Test
{
protected:
	FinallyPatternTests() : n(0), m(0)
	{
	}

	void test_one()
	{
		rz::finally f([this]{
			n = 1;
		});
		
		n = 2;
	}

	void test_two()
	{
		rz::finally f([this]{
			n = 1;
		});
		
		rz::finally g([this]{
			m = 10;
		});
		
		n = 2;
		m = 20;
	}
	
	void test_with_cancel()
	{
		rz::finally f([this]{
			n = 1;
		});
		
		rz::finally g([this]{
			m = 10;
		});
		
		n = 2;
		m = 20;
		
		g.cancel();
	}
	
	int n;
	int m;
};

TEST_F(FinallyPatternTests, FinalBlockIsCalled)
{
	test_one();
	
	EXPECT_EQ(1, n);
}

TEST_F(FinallyPatternTests, TwoFinalBlocksAreCalled)
{
	test_two();
	
	EXPECT_EQ(1, n);
	EXPECT_EQ(10, m);
}

TEST_F(FinallyPatternTests, Cancel)
{
	test_with_cancel();
	
	EXPECT_EQ(1, n);
	EXPECT_EQ(20, m);
}