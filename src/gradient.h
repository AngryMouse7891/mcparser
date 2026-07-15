#ifndef GRADIENT_H
#define GRADIENT_H

#include <iostream>
#include <string>
#include <cstdint>
#include <cmath>

// 设置终端启用ANSI颜色（仅Windows需要）
#ifdef _WIN32
#include <windows.h>
void enableAnsiColor()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

void printGradientRGB(const std::string& text, 
                      uint8_t r1,uint8_t g1,uint8_t b1,
                      uint8_t r2,uint8_t g2,uint8_t b2);
#endif