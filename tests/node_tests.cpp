#include "tests.h"

#include <string>
#include <algorithm>

// hack crz
#include "../src/impl/rz_core_dom_node_impl.h"

static std::string xml =
"<rootNode name=\"apple\">"
"	<secondNode name=\"pear\">things</secondNode>"
"	white"
"</rootNode>";

class NodeTests : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        doc.parse(xml);
    }
    
	rz::dom_document doc;
};

TEST_F(NodeTests, DefaultConstructedImplIsFalse)
{
    rz::dom_node_impl impl;
    
    bool b = impl;
    EXPECT_FALSE(b);
    
    EXPECT_FALSE(impl);
}

TEST_F(NodeTests, DefaultConstructedNodeIsFalse)
{
    rz::dom_node node;
    
    bool b = node;
    EXPECT_FALSE(b);
    
    EXPECT_FALSE(node);
}

TEST_F(NodeTests, AssignmentOperator)
{
	rz::dom_node node1;

	rz::dom_node node2 = node1;

	bool b = node1 == node2;

	EXPECT_TRUE(b);
}

TEST_F(NodeTests, DefaultConstructedNodesAreEqual)
{
    rz::dom_node node1;
    rz::dom_node node2;
    
    bool b = node1 == node2;
    
    EXPECT_TRUE(b);
}

TEST_F(NodeTests, GetName)
{
    EXPECT_EQ(std::string("rootNode"), doc.get_name());
}

TEST_F(NodeTests, GetValue)
{
    EXPECT_EQ(std::string("white"), doc.get_value());
}

TEST_F(NodeTests, GetRootNodeByCopyCtor)
{
    rz::dom_node root(doc);
    
    EXPECT_EQ(std::string("rootNode"), root.get_name());
}

TEST_F(NodeTests, GetRootNodeByAssignment)
{
    rz::dom_node root;
    
    root = doc;
    
    EXPECT_EQ(std::string("rootNode"), root.get_name());
}

TEST_F(NodeTests, GetSecondNode)
{
    auto node = doc.get_first_child();
    
    EXPECT_EQ(std::string("secondNode"), node.get_name());
}

TEST_F(NodeTests, ValidNodeIsTrue)
{
    auto node = doc.get_first_child();
    
    EXPECT_TRUE(node);
}

TEST_F(NodeTests, InvalidNodeIsFalse)
{
    auto sibling = doc.get_next_sibling();
    EXPECT_FALSE(sibling);
}

TEST_F(NodeTests, OperationOnInvalidNodeIsSafe)
{
    auto sibling = doc.get_next_sibling();
    EXPECT_FALSE(sibling);
    
    auto sibling2 = sibling.get_next_sibling();
    EXPECT_FALSE(sibling2);
    
    auto sibling3 = sibling.get_next_sibling();
    EXPECT_FALSE(sibling3);
}

TEST_F(NodeTests, GetSecondNodeAttributes)
{
    auto node = doc.get_first_child();
    auto attrs = rz::dom_attributes(node);
    
    auto begin = attrs.begin();
    auto end = attrs.end();
    
    auto distance = std::distance(begin, end);
    
    EXPECT_EQ(distance, 1);
}

TEST_F(NodeTests, GetSecondNodeAttribute)
{
    auto node = doc.get_first_child();
    auto attrs = rz::dom_attributes(node);
    auto attr = *attrs.begin();
    
    EXPECT_EQ(std::string("name"), attr.get_name());
    EXPECT_EQ(std::string("pear"), attr.get_value());
}

TEST_F(NodeTests, GetSecondNodeAttributeInline)
{
    // crz: this works because the node stays in scope long enough to
    // deref the attribute and copy the rapidxml node
    // crz: this does not work in xcode
    
    auto c = doc.get_first_child();
    auto r = rz::dom_attributes(c);
    
    auto attr = *(r.begin());
    
    EXPECT_EQ(std::string("name"), attr.get_name());
    EXPECT_EQ(std::string("pear"), attr.get_value());
}
