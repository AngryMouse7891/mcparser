#include<fmt/base.h>
#include<iostream>
#include<string>
#include "termcolor/termcolor.hpp"

void info_print(std::string msg){
    fmt::print("\033[36m[ℹ️] {}\033[0m\n",msg);
}

void warning_print(std::string msg){
    fmt::print("\033[33m[⚠] {}\033[0m\n",msg);
}

void error_print(std::string msg){
    std::cerr<<termcolor::red<<"[❌] "<<msg<<termcolor::reset<<'\n';
}

void success_print(std::string msg){
    fmt::print("\033[32m[✅] {}\033[0m\n",msg);
}