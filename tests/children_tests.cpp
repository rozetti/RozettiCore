#include "tests.h"

TEST(ChildrenTests, GetFirstChild_byName)
{
    std::string xml = "<a><b>b</b><c>c</c></a>";
    
    rz::dom_document doc;
    doc.parse(xml);
    
    rz::dom_node c = doc.get_first_child("c");
    
    ASSERT_STREQ("c", c.get_name().c_str());
}