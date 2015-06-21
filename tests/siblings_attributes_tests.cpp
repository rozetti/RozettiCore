#include "tests.h"

#include <vector>
#include <algorithm>

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

class SiblingsAttributesTests : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        doc.parse(xml);
    }

    rz::dom_document doc;
};

TEST_F(SiblingsAttributesTests, RangeAssignment)
{
    auto sibling = doc.get_first_child().get_next_sibling();
    auto sibling2 = sibling.get_next_sibling();
    rz::range<rz::dom_node> attrs = rz::dom_attributes(sibling2);
    
    rz::dom_node node(*attrs.begin());
    EXPECT_TRUE(node);
}

TEST_F(SiblingsAttributesTests, RangeAssignment2)
{
    rz::dom_node level(doc.get_first_child().get_next_sibling().get_next_sibling());
    rz::range<rz::dom_node> attrs = rz::dom_attributes(level);
    
    rz::dom_node node(*attrs.begin());
    EXPECT_TRUE(node);
}

TEST_F(SiblingsAttributesTests, SiblingsRangeFor)
{
    rz::dom_node modules(doc.get_first_child().get_next_sibling());
    
    for(auto module : rz::dom_siblings(modules))
    {
        EXPECT_TRUE(true) << (module.get_name() + "=" + module.get_value() + "\n").c_str();
    }
}

TEST_F(SiblingsAttributesTests, AttributesRangeFor)
{
    rz::dom_node level(doc.get_first_child().get_next_sibling().get_next_sibling());
    
    int i = 0;
    for(auto attr : rz::dom_attributes(level))
    {
        EXPECT_TRUE(true) << (attr.get_name() + "=" + attr.get_value() + "\n").c_str();
        
        std::string should_be;
        
        switch(i++)
        {
            case 0:
                should_be = "1";
                break;
            case 1:
                should_be = "2";
                break;
            case 2:
                should_be = "3";
                break;
            default:
                EXPECT_TRUE(false) << "serious fail";
        }
        
        EXPECT_EQ(should_be, attr.get_value());
    }
}

TEST_F(SiblingsAttributesTests, DefaultRangeFor)
{
    auto modules = doc.get_first_child().get_next_sibling();
    
    int i = 0;
    for(auto module : modules)
    {
        std::string should_be;
        
        switch(i++)
        {
            case 0:
                should_be = "Finance";
                break;
            case 1:
                should_be = "Admin";
                break;
            case 2:
                should_be = "HR";
                break;
            default:
                EXPECT_TRUE(false) << "serious fail";
        }
        
        EXPECT_EQ(should_be, module.get_value());
    }
}
