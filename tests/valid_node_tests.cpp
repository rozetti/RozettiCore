#include "tests.h"

TEST(ValidNode, DefaultConstructedNodeIsFalse)
{
    rz::dom_node node;
    
    EXPECT_FALSE(node);
}

TEST(ValidNode, EmptyNodeAsFloatEqualsDefault)
{
    rz::dom_node node;
    
    float f = node.get_value_as_float(1729.0f);
    
    EXPECT_EQ(1729.0f, f);
}

TEST(ValidNode, EmptyNodeAsDoubleEqualsDefault)
{
    rz::dom_node node;
    
    double d = node.get_value_as_float(1729.0);
    
    EXPECT_EQ(1729.0, d);
}

TEST(ValidNode, EmptyNodeAsIntEqualsDefault)
{
    rz::dom_node node;
    
    int i = node.get_value_as_int(1729);
    
    EXPECT_EQ(1729, i);
}

TEST(ValidNode, EmptyNodeAsEqualsEmptyString)
{
    rz::dom_node node;
    
    std::string s = node.get_value();
    
    EXPECT_EQ(std::string(""), s);
}
