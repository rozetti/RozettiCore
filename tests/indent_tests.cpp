#include "tests.h"

#include <string>

TEST(IndentTests, OneLineNoCR)
{
    std::string s_in = "abc";
    
    std::string s_out = rz::indent_lines_with_tab(s_in);
    
    ASSERT_STREQ("\tabc\n", s_out.c_str());
}

TEST(IndentTests, OneLineWithCR)
{
    std::string s_in = "abc\n";
    
    std::string s_out = rz::indent_lines_with_tab(s_in);
    
    ASSERT_STREQ("\tabc\n", s_out.c_str());
}

TEST(IndentTests, TwoLinesNoCR)
{
    std::string s_in = "abc\ndef";
    
    std::string s_out = rz::indent_lines_with_tab(s_in);
    
    ASSERT_STREQ("\tabc\n\tdef\n", s_out.c_str());
}

TEST(IndentTests, TwoLinesWithCR)
{
    std::string s_in = "abc\ndef\n";
    
    std::string s_out = rz::indent_lines_with_tab(s_in);
    
    ASSERT_STREQ("\tabc\n\tdef\n", s_out.c_str());
}


