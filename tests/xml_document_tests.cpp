#include "tests.h"

#include <string>
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

static std::string bad_xml =
"<debug thing=\"apple\"><"
"	<filename>debug.log</filename>"
"    <modules>"
"        <module>Finance</module>"
"        <module>Admin</module>"
"        <module>HR</module>"
"    </modules>"
"    <level a=\"1\" b=\"2\" c=\"3\">2</level>"
"hello"
"</debug>";

TEST(ParseTests, ParseReturnsFalseAndDoesNotThrowWithEmptyXML)
{
	rz::dom_document doc;

	bool b = true;

	EXPECT_NO_THROW(b = doc.parse(""));

	EXPECT_FALSE(b);
}

TEST(ParseTests, ParseReturnsFalseAndDoesNotThrowWithBadXML)
{
	rz::dom_document doc;
	
    bool b = true;
    
    // todo crz: this _does_ throw, need to look at how this test works
    EXPECT_NO_THROW(b = doc.parse(bad_xml));
	
	EXPECT_FALSE(b);
}

TEST(ParseTests, ParseReturnsTrueWithGoodXML)
{
	rz::dom_document doc;
	
	bool b = doc.parse(xml);
	
	EXPECT_TRUE(b);
}

class SimpleXMLParseTests : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        doc.parse(xml);
    }
    
	rz::dom_document doc;
};

TEST_F(SimpleXMLParseTests, DocumentGetRoot)
{
    EXPECT_EQ(std::string("debug"), doc.get_name());
}

TEST_F(SimpleXMLParseTests, GetRootFirstChild)
{
    auto node = doc.get_first_child();
    
    EXPECT_EQ(std::string("filename"), node.get_name());
}

TEST_F(SimpleXMLParseTests, GetRootFirstSibling)
{
    auto node = doc.get_first_child();
    
    auto sibling = node.get_next_sibling();
    
    EXPECT_EQ(std::string("modules"), sibling.get_name());
}

TEST_F(SimpleXMLParseTests, GetRootSecondSibling)
{
    auto node = doc.get_first_child();
    
    auto sibling1 = node.get_next_sibling();
    auto sibling2 = sibling1.get_next_sibling();
    
    EXPECT_EQ(std::string("level"), sibling2.get_name());
    EXPECT_EQ(std::string("2"), sibling2.get_value());
}

TEST_F(SimpleXMLParseTests, ThirdSiblingIsText)
{
    auto node = doc.get_first_child();
    
    auto sibling1 = node.get_next_sibling();
    auto sibling2 = sibling1.get_next_sibling();
    auto sibling3 = sibling2.get_next_sibling();
    
    EXPECT_EQ(std::string(""), sibling3.get_name());
    EXPECT_EQ(std::string("hello"), sibling3.get_value());
}

TEST_F(SimpleXMLParseTests, GetSecondLevelChildren)
{
    auto node = doc.get_first_child();
    auto node2 = node.get_next_sibling();
    
    auto node21 = node2.get_first_child();
    auto node22 = node21.get_next_sibling();
    auto node23 = node22.get_next_sibling();
    auto node24 = node23.get_next_sibling();
    
    EXPECT_TRUE(node21);
    EXPECT_EQ(std::string("module"), node21.get_name());
    EXPECT_EQ(std::string("Finance"), node21.get_value());
    
    EXPECT_TRUE(node22);
    EXPECT_EQ(std::string("module"), node22.get_name());
    EXPECT_EQ(std::string("Admin"), node22.get_value());
    
    EXPECT_TRUE(node23);
    EXPECT_EQ(std::string("module"), node23.get_name());
    EXPECT_EQ(std::string("HR"), node23.get_value());
    
    EXPECT_FALSE(node24);
}

TEST_F(SimpleXMLParseTests, DOM_EndIsFalse)
{
    auto it = doc.end();
    
    auto node = *it;
    
    EXPECT_FALSE(node);
}

TEST_F(SimpleXMLParseTests, AllChildrenAccessibleViaBegin)
{
    auto it = doc.begin();
    
    ++it;
    auto node = *it;
    EXPECT_TRUE(node);
    EXPECT_EQ(std::string("modules"), node.get_name());
    
    ++it;
    node = *it;
    EXPECT_TRUE(node);
    EXPECT_EQ(std::string("level"), node.get_name());
    
    ++it;
    node = *it;
    EXPECT_TRUE(node);
    EXPECT_EQ(std::string("hello"), node.get_value());
    
    ++it;
    node = *it;
    EXPECT_FALSE(node);
}

TEST_F(SimpleXMLParseTests, ForEach)
{
    auto begin = doc.begin_siblings();
    auto end = doc.end();
    
    std::for_each(begin, end, [](rz::dom_node it)
                  {
                      EXPECT_TRUE(it) << ((it.get_name() + "=" + it.get_value() + "\n").c_str());
                  });
}

TEST_F(SimpleXMLParseTests, BeginIsBeginChildren)
{
    auto it1 = doc.begin_children();
    auto it2 = doc.begin_attributes();
    auto it3 = doc.begin();
    
    EXPECT_TRUE(it1 == it3);
    EXPECT_FALSE(it2 == it3);
}

TEST_F(SimpleXMLParseTests, ForEachModule)
{
    auto dom = doc.get_first_child().get_next_sibling();
    
    std::for_each(dom.begin(), dom.end(), [](rz::dom_node it)
                  {
					EXPECT_TRUE(it) << (it.get_name() + "=" + it.get_value() + "\n").c_str();
                  });
}

TEST_F(SimpleXMLParseTests, FindModule)
{
    auto dom = doc.get_first_child().get_next_sibling();
    
    auto it = std::find_if(dom.begin(), dom.end(), [](rz::dom_node const &node)
                           {
                               return node.get_value() == "HR";
                           });
    
    EXPECT_TRUE(*it);
    EXPECT_EQ(std::string("module"), (*it).get_name());
    EXPECT_EQ(std::string("HR"), (*it).get_value());
}

TEST_F(SimpleXMLParseTests, FirstAttribute)
	{
    auto attr = doc.get_first_attribute();
    
    EXPECT_EQ(std::string("thing"), attr.get_name());
    EXPECT_EQ(std::string("apple"), attr.get_value());
}

TEST_F(SimpleXMLParseTests, BeginChildren)
{
    auto it = doc.begin_children();
    
    auto node = *it;
    EXPECT_TRUE(node);
    
    EXPECT_EQ(std::string("filename"), node.get_name());
}

TEST_F(SimpleXMLParseTests, BeginSiblings)
{
    auto it = doc.get_first_child().begin_siblings();
    
    auto node = *it;
    EXPECT_TRUE(node);
    
    EXPECT_EQ(std::string("modules"), node.get_name());
}

TEST_F(SimpleXMLParseTests, BeginAttributes)
{
    auto it = doc.begin_attributes();
    
    EXPECT_EQ(std::string("thing"), (*it).get_name());
    EXPECT_EQ(std::string("apple"), (*it).get_value());
}

TEST_F(SimpleXMLParseTests, Attributes)
{
    auto it = std::find_if(doc.begin(), doc.end(), [](rz::dom_node const &node)
                           {
                               return node.get_name() == "level";
                           });
    
    auto dom = *it;
    EXPECT_TRUE(dom);
    
    std::for_each(dom.begin_attributes(), dom.end(), [](rz::dom_node const &it)
                  {
				   EXPECT_TRUE(it) << (it.get_name() + "=" + it.get_value() + "\n").c_str();
                  });
}

TEST_F(SimpleXMLParseTests, FindValueNode)
{
    auto it = std::find_if(doc.begin(), doc.end(), [](rz::dom_node const &node)
                           {
                               return node.get_name() == "";
                           });
    
    EXPECT_TRUE(*it);
    EXPECT_EQ(std::string("hello"), (*it).get_value());
}

TEST_F(SimpleXMLParseTests, ValueConversion)
{
    auto node = doc.get_first_child();
    
    auto sibling1 = node.get_next_sibling();
    auto sibling2 = sibling1.get_next_sibling();
    
    int i = sibling2.get_value_as_int(0);
    EXPECT_EQ(2, i);
    
    float f = sibling2.get_value_as_float(0);
    EXPECT_EQ(2.0f, f);
    
    double d = sibling2.get_value_as_double(0);
    EXPECT_EQ(2.0, d);
}

TEST_F(SimpleXMLParseTests, NodeCtor)
{
    rz::dom_node level(doc.get_first_child().get_next_sibling().get_next_sibling());
    EXPECT_TRUE(level);
}

TEST_F(SimpleXMLParseTests, NodeAssignment)
{
    rz::dom_node level = doc.get_first_child().get_next_sibling().get_next_sibling();
    EXPECT_TRUE(level);
}
