#include <string>
#include <iostream>
#include "input_beautify.h"
#include "termcolor/termcolor.hpp"

std::string beautified_input(std::string prompt){
    std::cout<<termcolor::blue<<'['<<termcolor::bright_blue<<prompt<<termcolor::blue<<']'<<termcolor::yellow<<"> "<<termcolor::reset;
    std::string result;
    std::cin>>result;
    return result;
}