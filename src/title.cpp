#include "termcolor/termcolor.hpp"
#include <iostream>
#include <fmt/format.h>
#include "version.h"
#include "gradient.h"

using namespace std;

string title_str=R"(
 _____ ______   ________  ________  ________  ________  ________  _______   ________     
|\   _ \  _   \|\   ____\|\   __  \|\   __  \|\   __  \|\   ____\|\  ___ \ |\   __  \    
\ \  \\\__\ \  \ \  \___|\ \  \|\  \ \  \|\  \ \  \|\  \ \  \___|\ \   __/|\ \  \|\  \   
 \ \  \\|__| \  \ \  \    \ \   ____\ \   __  \ \   _  _\ \_____  \ \  \_|/_\ \   _  _\  
  \ \  \    \ \  \ \  \____\ \  \___|\ \  \ \  \ \  \\  \\|____|\  \ \  \_|\ \ \  \\  \| 
   \ \__\    \ \__\ \_______\ \__\    \ \__\ \__\ \__\\ _\ ____\_\  \ \_______\ \__\\ _\ 
    \|__|     \|__|\|_______|\|__|     \|__|\|__|\|__|\|__|\_________\|_______|\|__|\|__|
                                                          \|_________|                   
                                                                                         
                                                                                         
)";

void print_title(){
    printGradientRGB(title_str,34,139,34,139,69,19);
    cout<<'\n';
    printGradientRGB(fmt::format("Version     {}",VERSION_STRING),144,202,249,244,133,177);
    printGradientRGB(fmt::format("BuildTime   {}",BUILD_TIME),144,202,249,244,133,177);
    printGradientRGB(fmt::format("GitHash     {}",GIT_HASH),144,202,249,244,133,177);
    printGradientRGB(fmt::format("GitBranch   {}",GIT_BRANCH),144,202,249,244,133,177);
    printGradientRGB(fmt::format("Homepage    {}",PROJECT_HOMEPAGE_URL),144,202,249,244,133,177);
    cout<<'\n';
}