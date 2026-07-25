#ifndef PRINT_BEAUTIFY_H
#define PRINT_BEAUTIFY_H

#include<fmt/base.h>
#include<iostream>
#include<string>
#include "termcolor/termcolor.hpp"

void info_print(std::string msg);

void warning_print(std::string msg);

void error_print(std::string msg);

void success_print(std::string msg);

#endif