#include "tests.h"

#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

static std::string xml =
"<?xml version=\"1.0\"?>\n"
"<TableConfig xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" Name=\"awesome\">\n"
"  <Props>\n"
"    <PropConfig Name=\"Stopper_LG\" X=\"0.017468214\" Y=\"6.91957426\" Z=\"-31.4959583\" R=\"90\">\n"
"		hello\n"
"		<bin>blah</bin>\n"
"	</PropConfig>\n"
"    <PropConfig Name=\"zone1\" X=\"0.0245952122\" Y=\"6.91957426\" Z=\"-28.2875\" R=\"0\" />\n"
"    <PropConfig Name=\"zone2\" X=\"-0.061304152\" Y=\"6.91957426\" Z=\"-23.1300354\" R=\"0\" />\n"
"    <PropConfig Name=\"zone3\" X=\"-0.08795121\" Y=\"6.91957426\" Z=\"-19.7075424\" R=\"0\" />\n"
"    <PropConfig Name=\"coin\" X=\"0.489138842\" Y=\"7\" Z=\"-17.7573586\" R=\"0\" />\n"
"    <PropConfig Name=\"coin\" X=\"0.4726255\" Y=\"7\" Z=\"-14.5928926\" R=\"0\" />\n"
"    <PropConfig Name=\"coin\" X=\"-1.52047551\" Y=\"7\" Z=\"-7.815818\" R=\"0\" />\n"
"    <PropConfig Name=\"coin\" X=\"-1.54971278\" Y=\"7\" Z=\"-4.04138\" R=\"0\" />\n"
"    <PropConfig Name=\"coin\" X=\"1.51094782\" Y=\"7\" Z=\"-1.27588534\" R=\"0\" />\n"
"    <PropConfig Name=\"coin\" X=\"1.53619993\" Y=\"7\" Z=\"2.14440632\" R=\"0\" />\n"
"    <PropConfig Name=\"coin\" X=\"-0.319735736\" Y=\"7\" Z=\"10.0530939\" R=\"0\" />\n"
"    <PropConfig Name=\"coin\" X=\"-0.303751\" Y=\"7\" Z=\"6.751972\" R=\"0\" />\n"
"    <PropConfig Name=\"coin\" X=\"-0.327003837\" Y=\"7\" Z=\"13.7334108\" R=\"0\" />\n"
"    <PropConfig Name=\"coin\" X=\"1.49776351\" Y=\"6.91957426\" Z=\"-4.50952148\" R=\"0\" />\n"
"    <PropConfig Name=\"coin\" X=\"-1.52298653\" Y=\"6.91957426\" Z=\"-11.96119\" R=\"0\" />\n"
"    <PropConfig Name=\"coin\" X=\"0.5322576\" Y=\"6.91957426\" Z=\"-21.668211\" R=\"0\" />\n"
"  </Props>\n"
"</TableConfig>";

class DOMCoinsTests : public ::testing::Test
{
protected:
    rz::dom_document doc;
    
    virtual void SetUp()
    {
        doc.parse(xml);
    }
};

TEST_F(DOMCoinsTests, HardWorkParse)
{
    std::vector<rz::dom_node> nodes;
    
    auto props = doc.get_first_child();
    
    std::copy_if(props.begin(), props.end(), std::back_inserter(nodes), [](rz::dom_node const &node)
                 {
                     EXPECT_EQ(std::string("PropConfig"), node.get_name());
                     
                     auto c = std::count_if(node.begin_attributes(), node.end(), [](rz::dom_node const &attr)
                                           {
                                               return attr.get_name() == "Name" && attr.get_value() == "coin";
                                           });
                     
                     return c != 0;
                 });
    
    std::for_each(nodes.begin(), nodes.end(), [](rz::dom_node &node)
                  {
                      ASSERT_TRUE(node);
                      
                      std::stringstream ss;
                      ss << node.get_name() << ":";
                      
                      std::for_each(node.begin_attributes(), node.end(), [&ss](rz::dom_node const &attr)
                                    {
                                        ss << " " << attr.get_name() << "=" << attr.get_value();
                                    });
                      
                      ss << std::endl;
                      
//                      Logger::WriteMessage(ss.str().c_str());
                  });
}

TEST_F(DOMCoinsTests, RangeFor)
{
    auto props = doc.get_first_child();
    
    for(auto const &node : rz::dom_children(props))
    {
        ASSERT_TRUE(node);
        
        std::stringstream ss;
        ss << node.get_name() << ":";
        
        for (auto const &attr : rz::dom_attributes(node))
        {
            ss << " " << attr.get_name() << "=" << attr.get_value();
        }
        
        ss << std::endl;
        
//        Logger::WriteMessage(ss.str().c_str());
    }
}

TEST_F(DOMCoinsTests, CoinAttributes)
{
    auto coin = doc.get_first_child()
    .get_first_child()
    .get_next_sibling()
    .get_next_sibling()
    .get_next_sibling()
    .get_next_sibling();
    
    //<PropConfig Name="coin" X="0.489138842" Y="7" Z="-17.7573586" R="0" />"
    
    std::string name = coin.get_attribute("Name").get_value();
    float x = coin.get_attribute("X").get_value_as_float(0);
    float y = coin.get_attribute("Y").get_value_as_float(0);
    float z = coin.get_attribute("Z").get_value_as_float(0);
    int r = coin.get_attribute("R").get_value_as_int(0);
    float angular_speed_factor = coin.get_attribute("angularSpeedFactor").get_value_as_float(123.4f);
    float throw_factor = coin.get_attribute("throwFactor").get_value_as_float(234.5f);
    
    EXPECT_EQ(std::string("coin"), name);
    EXPECT_EQ(0.489138842f, x);
    EXPECT_EQ(7.0f, y);
    EXPECT_EQ(-17.7573586f, z);
    EXPECT_EQ(0, r);
    EXPECT_EQ(123.4f, angular_speed_factor);
    EXPECT_EQ(234.5f, throw_factor);
}
