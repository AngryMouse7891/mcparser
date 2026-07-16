#ifndef GRADIENT_H
#define GRADIENT_H

#include <fmt/base.h>
#include <string>
#include <cstdint>
#include <cmath>

typedef long long ll;

// 设置终端启用ANSI颜色（仅Windows需要）
#ifdef _WIN32
#include <windows.h>
void enableAnsiColor();
#endif

void printGradientRGB(const std::string& text, 
                      uint8_t r1,uint8_t g1,uint8_t b1,
                      uint8_t r2,uint8_t g2,uint8_t b2);
#endif