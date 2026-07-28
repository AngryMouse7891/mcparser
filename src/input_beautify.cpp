#include <string>
#include <iostream>
#include "input_beautify.h"
#include "termcolor/termcolor.hpp"
#include "print_beautify.h"
#include "input_beautify.h"
typedef long long ll;
#ifdef _WIN32
#include <windows.h>
ll outputCP = GetConsoleOutputCP();
#endif

std::string beautified_input(std::string prompt,bool required){
    if (required)
    {
        std::cout<<termcolor::red<<" * "<<termcolor::cyan<<prompt<<termcolor::white<<" ==> "<<termcolor::reset<<std::flush;
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
        #if _WIN32
            SetConsoleOutputCP(outputCP); // 设置控制台输出为系统原编码
        #endif
        exit(1);
    }
    return result;
}
