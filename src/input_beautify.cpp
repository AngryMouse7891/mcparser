#include <string>
#include <iostream>
#include "input_beautify.h"
#include "termcolor/termcolor.hpp"

std::string beautified_input(std::string prompt){
    std::cout<<termcolor::cyan<<prompt<<termcolor::white<<" ==> "<<termcolor::reset<<std::flush;
    std::string result;
    std::cin>>result;
    return result;
}