#include <string>
#include <iostream>
#include "input_beautify.h"
#include "termcolor/termcolor.hpp"
#include "print_beautify.h"

std::string beautified_input(std::string prompt,bool required){
    if (required)
    {
        std::cout<<termcolor::red<<'*'<<termcolor::cyan<<prompt<<termcolor::white<<" ==> "<<termcolor::reset<<std::flush;
    }
    else
    {
        std::cout<<termcolor::cyan<<prompt<<termcolor::white<<" ==> "<<termcolor::reset<<std::flush;
    }
    std::string result;
    std::cin>>result;
    if (result.empty() && required)
    {
        error_print("未输入必填项！");
        exit(1);
    }
    return result;
}
