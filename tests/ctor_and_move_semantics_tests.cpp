#include "tests.h"

#include <iostream>
#include <vector>

class class1
{
public:
	class1() : m_i(0), m_v{1,2,3,4}
	{
		std::cout << "class1 default ctor" << std::endl;
		}
		
		class1(int i, std::vector<int> v) : m_i(i), m_v(v)
		{
			std::cout << "class1 ctor(int,vector)" << std::endl;
		}
		
		class1(class1 const &other) : m_i(other.m_i), m_v(other.m_v)
		{
			std::cout << "class1 copy ctor" << std::endl;
		}
		
		class1(class1 &&other) : class1()
		{
			std::cout << "class1 move ctor" << std::endl;
			swap(*this, other);
		}
		
		class1 &operator=(class1 const &other)
		{
			std::cout << "class1 const ref assignment" << std::endl;
			
			class1 tmp(other);
			swap(*this, tmp);
			return *this;
		}
		
		class1 &operator=(class1 &&other)
		{
			std::cout << "class1 move assignment" << std::endl;
			swap(*this, other);
			return *this;
		}
		
		friend void swap(class1 &l, class1 &r)
		{
			std::cout << "class1 friend swap" << std::endl;
			
			using std::swap;
			
			swap(l.m_i, r.m_i);
			swap(l.m_v, r.m_v);
		}
		
		int m_i;
		std::vector<int> m_v;
		};
		
		TEST(MoveTests, DefaultCtor)
		{
			class1 c1;
			
			EXPECT_EQ(0, c1.m_i);
			EXPECT_EQ(4, c1.m_v.size());
			EXPECT_EQ(1, c1.m_v[0]);
			EXPECT_EQ(2, c1.m_v[1]);
			EXPECT_EQ(3, c1.m_v[2]);
			EXPECT_EQ(4, c1.m_v[3]);
		}
		
		TEST(MoveTests, IntCtor)
		{
			class1 c1{1729, {2,3,4}};
			
			EXPECT_EQ(1729, c1.m_i);
			EXPECT_EQ(3, c1.m_v.size());
			EXPECT_EQ(2, c1.m_v[0]);
			EXPECT_EQ(3, c1.m_v[1]);
			EXPECT_EQ(4, c1.m_v[2]);
		}
		
		TEST(MoveTests, CopyCtor)
		{
			class1 c1{1729, {2,3,4}};
			class1 c2{c1};
			
			EXPECT_EQ(1729, c1.m_i);
			EXPECT_EQ(3, c1.m_v.size());
			EXPECT_EQ(2, c1.m_v[0]);
			EXPECT_EQ(3, c1.m_v[1]);
			EXPECT_EQ(4, c1.m_v[2]);
			
			EXPECT_EQ(1729, c2.m_i);
			EXPECT_EQ(3, c1.m_v.size());
			EXPECT_EQ(2, c2.m_v[0]);
			EXPECT_EQ(3, c2.m_v[1]);
			EXPECT_EQ(4, c2.m_v[2]);
		}
		
		TEST(MoveTests, Swap)
		{
			class1 c1;
			class1 c2{1729, {}};
			
			EXPECT_EQ(0, c1.m_i);
			EXPECT_EQ(4, c1.m_v.size());
			EXPECT_EQ(1, c1.m_v[0]);
			EXPECT_EQ(2, c1.m_v[1]);
			EXPECT_EQ(3, c1.m_v[2]);
			EXPECT_EQ(4, c1.m_v[3]);
			
			EXPECT_EQ(1729, c2.m_i);
			EXPECT_EQ(0, c2.m_v.size());
			
			swap(c1, c2);
			
			EXPECT_EQ(1729, c1.m_i);
			EXPECT_EQ(0, c1.m_v.size());
			
			EXPECT_EQ(0, c2.m_i);
			EXPECT_EQ(4, c2.m_v.size());
			EXPECT_EQ(1, c2.m_v[0]);
			EXPECT_EQ(2, c2.m_v[1]);
			EXPECT_EQ(3, c2.m_v[2]);
			EXPECT_EQ(4, c2.m_v[3]);
		}
		
		TEST(MoveTests, MoveCtor)
		{
			class1 c1{1729, {2,3,4}};
			class1 c2{std::move(c1)};
			
			EXPECT_EQ(0, c1.m_i);
			EXPECT_EQ(4, c1.m_v.size());
			EXPECT_EQ(1, c1.m_v[0]);
			EXPECT_EQ(2, c1.m_v[1]);
			EXPECT_EQ(3, c1.m_v[2]);
			EXPECT_EQ(4, c1.m_v[3]);
			
			EXPECT_EQ(1729, c2.m_i);
			EXPECT_EQ(3, c2.m_v.size());
			EXPECT_EQ(2, c2.m_v[0]);
			EXPECT_EQ(3, c2.m_v[1]);
			EXPECT_EQ(4, c2.m_v[2]);
		}
		
		TEST(MoveTests, ConstRefAssignment)
		{
			class1 c1{1729, {2,3,4}};
			class1 c2;
			c2 = c1;
			
			EXPECT_EQ(1729, c1.m_i);
			EXPECT_EQ(3, c1.m_v.size());
			EXPECT_EQ(2, c1.m_v[0]);
			EXPECT_EQ(3, c1.m_v[1]);
			EXPECT_EQ(4, c1.m_v[2]);
			
			EXPECT_EQ(1729, c2.m_i);
			EXPECT_EQ(3, c1.m_v.size());
			EXPECT_EQ(2, c2.m_v[0]);
			EXPECT_EQ(3, c2.m_v[1]);
			EXPECT_EQ(4, c2.m_v[2]);
		}
		
		TEST(MoveTests, MoveAssignment)
		{
			class1 c1{1729, {2,3,4}};
			class1 c2;
			c2 = std::move(c1);
			
			EXPECT_EQ(0, c1.m_i);
			EXPECT_EQ(4, c1.m_v.size());
			EXPECT_EQ(1, c1.m_v[0]);
			EXPECT_EQ(2, c1.m_v[1]);
			EXPECT_EQ(3, c1.m_v[2]);
			EXPECT_EQ(4, c1.m_v[3]);
			
			EXPECT_EQ(1729, c2.m_i);
			EXPECT_EQ(3, c2.m_v.size());
			EXPECT_EQ(2, c2.m_v[0]);
			EXPECT_EQ(3, c2.m_v[1]);
			EXPECT_EQ(4, c2.m_v[2]);
		}
		
		class class2
		{
		public:
			class2() : m_i(0), m_v{1,2,3,4}
			{
				std::cout << "class2 default ctor" << std::endl;
			}
			
			class2(int i, std::vector<int> v) : m_i(i), m_v(v)
			{
				std::cout << "class2 ctor(int,vector)" << std::endl;
			}
			
			class2 &operator=(class2 other)
			{
				std::cout << "class2 value assignment" << std::endl;
				swap(*this, other);
				return *this;
			}
			
			friend void swap(class2 &l, class2 &r)
			{
				std::cout << "class2 friend swap" << std::endl;
				
				using std::swap;
				
				swap(l.m_i, r.m_i);
				swap(l.m_v, r.m_v);
			}
			
			int m_i;
			std::vector<int> m_v;
		};
				
		TEST(MoveTests, ValueAssignment)
		{
			class2 c1{1729, {2,3,4}};
			class2 c2;
			c2 = c1;
			
			EXPECT_EQ(1729, c1.m_i);
			EXPECT_EQ(3, c1.m_v.size());
			EXPECT_EQ(2, c1.m_v[0]);
			EXPECT_EQ(3, c1.m_v[1]);
			EXPECT_EQ(4, c1.m_v[2]);
			
			EXPECT_EQ(1729, c2.m_i);
			EXPECT_EQ(3, c1.m_v.size());
			EXPECT_EQ(2, c2.m_v[0]);
			EXPECT_EQ(3, c2.m_v[1]);
			EXPECT_EQ(4, c2.m_v[2]);
		}
		
		TEST(MoveTests, ValueMoveAssignment)
		{
			class2 c1{1729, {2,3,4}};
			class2 c2;
			c2 = std::move(c1); // todo crz: it is not clear that this is better than const ref/move assignment
			
			EXPECT_EQ(1729, c1.m_i);
			EXPECT_EQ(3, c1.m_v.size());
			EXPECT_EQ(2, c1.m_v[0]);
			EXPECT_EQ(3, c1.m_v[1]);
			EXPECT_EQ(4, c1.m_v[2]);
			
			EXPECT_EQ(1729, c2.m_i);
			EXPECT_EQ(3, c2.m_v.size());
			EXPECT_EQ(2, c2.m_v[0]);
			EXPECT_EQ(3, c2.m_v[1]);
			EXPECT_EQ(4, c2.m_v[2]);
		}
