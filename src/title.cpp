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

void set_title(){
    string console_title=fmt::format("title MCParser v{} (Git hash {}) - {}",VERSION_STRING,GIT_HASH,AUTHOR);
    #if _WIN32
    system(console_title);
    #endif
}

void print_title(){
    printGradientRGB(title_str,34,139,34,139,69,19);
    printGradientRGB(fmt::format("By {}",AUTHOR),255,76,0,75,92,196);
    fmt::print("\n");
    printGradientRGB(fmt::format("Version     {}",VERSION_STRING),144,202,249,244,133,177);
    printGradientRGB(fmt::format("BuildTime   {}",BUILD_TIME),144,202,249,244,133,177);
    printGradientRGB(fmt::format("GitHash     {}",GIT_HASH),144,202,249,244,133,177);
    printGradientRGB(fmt::format("GitBranch   {}",GIT_BRANCH),144,202,249,244,133,177);
    printGradientRGB(fmt::format("Homepage    {}",PROJECT_HOMEPAGE_URL),144,202,249,244,133,177);
    fmt::print("\n");
    printGradientRGB(fmt::format("JsonCpp     {}",JSONCPP_VERSION_STRING),255,235,59,176,164,227);
    printGradientRGB(fmt::format("fmt         {}",FMT_VERSION_STRING),255,235,59,176,164,227);
    printGradientRGB(fmt::format("Libcurl     {}",LIBCURL_VERSION_STRING),255,235,59,176,164,227);
    printGradientRGB(fmt::format("OpenSSL     {}",OPENSSL_VERSION_STRING),255,235,59,176,164,227);
    printGradientRGB(fmt::format("Tabulate    {}",TABULATE_VERSION_STRING),255,235,59,176,164,227);
    printGradientRGB(fmt::format("Termcolor   {}",TERMCOLOR_VERSION_STRING),255,235,59,176,164,227);
    fmt::print("\n");
}