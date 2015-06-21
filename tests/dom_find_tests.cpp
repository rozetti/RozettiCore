#include "tests.h"

static std::string xml =
"<debug thing=\"apple\">"
"	<filename>debug.log</filename>"
"    <modules>"
"        <module>Finance</module>"
"        <module>Admin</module>"
"        <module>HR</module>"
"    </modules>"
"    <level a=\"1\" b=\"2\" c=\"3\">2</level>"
"hello"
"</debug>";

class DomFindTests : public ::testing::Test
{
protected:
    rz::dom_document doc;
    
    virtual void SetUp()
    {
        doc.parse(xml);
    }
};

TEST_F(DomFindTests, FindAttribute)
{
    auto level = doc.get_first_child().get_next_sibling().get_next_sibling();
    auto attrs = rz::dom_attributes(level);
    
    auto attr = rz::dom_node::find(attrs, std::string("b"));
    EXPECT_TRUE(attr);
    EXPECT_EQ(2, attr.get_value_as_int(0));
    
    attr = rz::dom_node::find(attrs, std::string("a"));
    EXPECT_TRUE(attr);
    EXPECT_EQ(1, attr.get_value_as_int(-1));
    
    attr = rz::dom_node::find(attrs, std::string("c"));
    EXPECT_TRUE(attr);
    EXPECT_EQ(3, attr.get_value_as_int(5));
}

TEST_F(DomFindTests, FailToFindAttribute)
{
    auto level = doc.get_first_child().get_next_sibling().get_next_sibling();
    auto attrs = rz::dom_attributes(level);
    
    auto attr = rz::dom_node::find(attrs, std::string("not_there"));
    EXPECT_FALSE(attr);
    
    attr = rz::dom_node::find(attrs, std::string(""));
    EXPECT_FALSE(attr);
    
    attr = rz::dom_node::find(attrs, std::string("\n"));
    EXPECT_FALSE(attr);
}

