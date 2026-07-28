#include "termcolor/termcolor.hpp"
#include <iostream>
#include <fmt/format.h>
#include <fmt/base.h>
#include "version.h"
#include "gradient.h"
#include "splashes.h"
#include "title.h"
#if _WIN32
#include <windows.h>
#endif

using namespace std;

string title_str=R"( ****     ****   ******  *******                                         
/**/**   **/**  **////**/**////**                                        
/**//** ** /** **    // /**   /**  ******   ******  ******  *****  ******
/** //***  /**/**       /*******  //////** //**//* **////  **///**//**//*
/**  //*   /**/**       /**////    *******  /** / //***** /******* /** / 
/**   /    /**//**    **/**       **////**  /**    /////**/**////  /**   
/**        /** //****** /**      //********/***    ****** //******/***   
//         //   //////  //        //////// ///    //////   ////// ///    
)";

void set_title(){
    string console_title=fmt::format("title MCParser v{} (Git hash {}) - {}",VERSION_STRING,GIT_HASH,AUTHOR);
    #if _WIN32
    system(console_title.c_str());
    #endif
}

void print_title(){
    fmt::print("\033[93m                                                                    {}\033[0m\n",rand_splash());
    printGradientRGB(title_str,34,139,34,139,69,19);
    printGradientRGB(fmt::format("By {}",AUTHOR),255,76,0,75,92,196);
    fmt::print("\n");
    printGradientRGB(fmt::format("Version            {}",VERSION_STRING),144,202,249,244,133,177);
    printGradientRGB(fmt::format("BuildTime          {}",BUILD_TIME),144,202,249,244,133,177);
    printGradientRGB(fmt::format("GitHash            {}",GIT_HASH),144,202,249,244,133,177);
    printGradientRGB(fmt::format("GitBranch          {}",GIT_BRANCH),144,202,249,244,133,177);
    printGradientRGB(fmt::format("Homepage           {}",PROJECT_HOMEPAGE_URL),144,202,249,244,133,177);
    printGradientRGB(fmt::format("LuoguHomepage      {}",LUOGU_HOMEPAGE),144,202,249,244,133,177);
    printGradientRGB(fmt::format("MCBBSHomepage      {}",MCBBS_HOMEPAGE),144,202,249,244,133,177);
    fmt::print("\n");
    printGradientRGB(fmt::format("JsonCpp            {}",JSONCPP_VERSION_STRING),255,235,59,176,164,227);
    printGradientRGB(fmt::format("fmt                {}",FMT_VERSION_STRING),255,235,59,176,164,227);
    printGradientRGB(fmt::format("Libcurl            {}",LIBCURL_VERSION_STRING),255,235,59,176,164,227);
    printGradientRGB(fmt::format("OpenSSL            {}",OPENSSL_VERSION_STRING),255,235,59,176,164,227);
    printGradientRGB(fmt::format("Tabulate           {}",TABULATE_VERSION_STRING),255,235,59,176,164,227);
    printGradientRGB(fmt::format("Termcolor          {}",TERMCOLOR_VERSION_STRING),255,235,59,176,164,227);
    fmt::print("\n");
}