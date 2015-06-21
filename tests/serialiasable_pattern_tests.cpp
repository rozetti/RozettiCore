#include "tests.h"

#include <sstream>
#include <string>

struct A : public rz::serialisable<>
{
	int m_a;
	
	A() : m_a(0) { }
	explicit A(int _a) : m_a(_a) { }

	std::string serialise() const;
	bool deserialise(std::string &serialised);
};

std::string A::serialise() const
{
	std::stringstream ss;
	
	ss << m_a;
	
	return ss.str();
}

bool A::deserialise(std::string &serialised)
{
	std::stringstream ss(serialised);
	
	ss >> m_a;
	
	return true;
}

TEST(SerialisableTests, PatternMakesSenseAndCanBeImplemented)
{
	A a(3);
	
	auto s = a.serialise();
	ASSERT_STRNE("", s.c_str());
	
	A b;
	
	EXPECT_EQ(0, b.m_a);
	EXPECT_TRUE(b.deserialise(s));
	EXPECT_EQ(3, b.m_a);
}

struct B : public rz::serialisable<std::string, rz::dom_node>
{
	int m_a;
	
	B() : m_a(0) { }
	explicit B(int _a) : m_a(_a) { }
	
	std::string serialise() const;
	bool deserialise(rz::dom_node &serialised);
};

std::string B::serialise() const
{
	std::stringstream ss;
	
	ss << "<B>" << m_a << "</B>";
	
	return ss.str();
}

bool B::deserialise(rz::dom_node &serialised)
{
	std::stringstream ss(serialised.get_value());
	
	ss >> m_a;
	
	return true;
}

TEST(SerialisableTests, DeserialiseFromDom)
{
	B a(3);
	
	auto s = a.serialise();
	ASSERT_STRNE("", s.c_str());
	
	s = "<Q>" + s + "</Q>";
	
	rz::dom_document doc;
	ASSERT_TRUE(doc.parse(s));
	
	auto node = doc.get_first_child();
	
	B b;
	
	EXPECT_EQ(0, b.m_a);
	EXPECT_TRUE(b.deserialise(node));
	EXPECT_EQ(3, b.m_a);
}

