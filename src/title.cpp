#include "termcolor/termcolor.hpp"
#include <iostream>
#include <fmt/format.h>
#include <fmt/base.h>
#include "version.h"
#include "gradient.h"
#include "splashes.h"
#include "title.h"
#include "get_repo_data.h"
#if _WIN32
#include <windows.h>
#endif

using namespace std;

string title_str=R"('##::::'##::'######::'########:::::'###::::'########:::'######::'########:'########::
 ###::'###:'##... ##: ##.... ##:::'## ##::: ##.... ##:'##... ##: ##.....:: ##.... ##:
 ####'####: ##:::..:: ##:::: ##::'##:. ##:: ##:::: ##: ##:::..:: ##::::::: ##:::: ##:
 ## ### ##: ##::::::: ########::'##:::. ##: ########::. ######:: ######::: ########::
 ##. #: ##: ##::::::: ##.....::: #########: ##.. ##::::..... ##: ##...:::: ##.. ##:::
 ##:.:: ##: ##::: ##: ##:::::::: ##.... ##: ##::. ##::'##::: ##: ##::::::: ##::. ##::
 ##:::: ##:. ######:: ##:::::::: ##:::: ##: ##:::. ##:. ######:: ########: ##:::. ##:
..:::::..:::......:::..:::::::::..:::::..::..:::::..:::......:::........::..:::::..::)";

void set_title(){
    string console_title=fmt::format("title MCParser v{} (r{}) - by {}",VERSION_STRING,GIT_HASH,AUTHOR);
    #if _WIN32
    system(console_title.c_str());
    #endif
}

void print_title(){
    fmt::print("\033[93m                                      {}\033[0m\n",rand_splash());
    printGradientRGB(title_str,82,127,70,69,47,30);
    print_data();
    printGradientRGB(fmt::format("By {}",AUTHOR),255,76,0,75,92,196);
    fmt::print("\n");
    printGradientRGB(fmt::format("v{} ● 编译日期 {} ● r{} ● 分支{}",VERSION_STRING,BUILD_TIME,GIT_HASH,GIT_BRANCH),144,202,249,244,133,177);
    cout<<termcolor::yellow<<"项目主页：https://www.mcbbs.co/thread-5638-1-1.html\n"<<termcolor::reset;
    fmt::print("\n");
}