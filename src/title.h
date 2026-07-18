#ifndef TITLE_H
#define TITLE_H

#include "termcolor/termcolor.hpp"
#include <iostream>
#include <fmt/format.h>
#include <fmt/base.h>
#include "version.h"
#include "gradient.h"
#if _WIN32
#include <windows.h>
#endif


using namespace std;

string title=R"(
 _____ ______   ________  ________  ________  ________  ________  _______   ________     
|\   _ \  _   \|\   ____\|\   __  \|\   __  \|\   __  \|\   ____\|\  ___ \ |\   __  \    
\ \  \\\__\ \  \ \  \___|\ \  \|\  \ \  \|\  \ \  \|\  \ \  \___|\ \   __/|\ \  \|\  \   
 \ \  \\|__| \  \ \  \    \ \   ____\ \   __  \ \   _  _\ \_____  \ \  \_|/_\ \   _  _\  
  \ \  \    \ \  \ \  \____\ \  \___|\ \  \ \  \ \  \\  \\|____|\  \ \  \_|\ \ \  \\  \| 
   \ \__\    \ \__\ \_______\ \__\    \ \__\ \__\ \__\\ _\ ____\_\  \ \_______\ \__\\ _\ 
    \|__|     \|__|\|_______|\|__|     \|__|\|__|\|__|\|__|\_________\|_______|\|__|\|__|
                                                          \|_________|                   
                                                                                         
)";

void set_title();

void print_title();

#endif