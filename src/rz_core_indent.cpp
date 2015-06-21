/* The RozettiCore Library. Copyright 2015 Conrad Rozetti, crz@rozetti.org. Distributed under the MIT License, see rz_core.h. */

#include "rz_core_indent.h"

#include <string>
#include <vector>
#include <istream>
#include <sstream>

namespace rz
{
    std::string indent_lines_with_tab(std::string const &xml)
    {
        std::istringstream stream(xml);
        std::string line;
        std::stringstream ss;
        
        while(std::getline(stream, line))
        {
            ss << "\t" << line << std::endl;
        }
        
        return ss.str();
    }
}