#include "tests.h"

static std::string xml =
"<root>"
"	<second>things</second>"
"	<secondSibling>stuff</secondSibling>"
"</root>";

class IteratorTests : public ::testing::Test
{
protected:
    rz::dom_document doc;
    
    virtual void SetUp()
    {
        doc.parse(xml);
    }
};

TEST_F(IteratorTests, DefaultConstructedIteratorsAreEqual)
{
    rz::dom_node::iterator it1;
    rz::dom_node::iterator it2;
    
    bool b = it1 == it2;
    
    EXPECT_TRUE(b);
}

TEST_F(IteratorTests, EndEqualsDefaultConstructedIterator)
{
    rz::dom_node::iterator it;
    auto end = doc.end();
    
    bool b = it == end;
    
    EXPECT_TRUE(b);
}

TEST_F(IteratorTests, PreIncrement)
{
    auto siblings = rz::dom_children(doc);
    
    auto it = siblings.begin();
    
    auto node1 = *it;
    auto value1 = node1.get_value();
    EXPECT_EQ(std::string("things"), value1);
    
    ++it;
    
    auto node2 = *it;
    auto value2 = node2.get_value();
    EXPECT_EQ(std::string("stuff"), value2);
}

TEST_F(IteratorTests, PostIncrement)
{
    auto siblings = rz::dom_children(doc);
    
    auto it = siblings.begin();
    
    auto node1 = *it;
    auto value1 = node1.get_value();
    EXPECT_EQ(std::string("things"), value1);
    
    it++;
    
    auto node2 = *it;
    auto value2 = node2.get_value();
    EXPECT_EQ(std::string("stuff"), value2);
}
