#include "tests.h"

static std::string xml =
"<rootNode name=\"apple\" aa=\"11\" bb=\"22\" cc=\"33\">"
"	<secondNode name=\"pear\" a=\"1\" b=\"2\" c=\"3\">things</secondNode>"
"	white"
"</rootNode>";

class AttributesTests : public testing::Test
{
protected:
    rz::dom_document doc;

    virtual void SetUp()
    {
        doc.parse(xml);
    }
};

TEST_F(AttributesTests, GetAttribute)
{
    auto attr = doc.get_attribute(std::string("bb"));
    
    EXPECT_TRUE(attr);
    
    EXPECT_EQ(std::string("22"), attr.get_value());
}

TEST_F(AttributesTests, GetMissingAttributeReturnsFalseNode)
{
    auto attr = doc.get_attribute(std::string("dd"));
    
    EXPECT_FALSE(attr);
}
