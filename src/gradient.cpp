#include <fmt/base.h>
#include <string>
#include <cstdint>
#include <cmath>

typedef long long ll;

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
                      uint8_t r2,uint8_t g2,uint8_t b2)
{
    size_t len = text.size();
    for(size_t i=0;i<len;i++)
    {
        double t = 1.0f*i / std::max<size_t>(1,len-1);
        uint8_t r = r1 + t*(r2-r1);
        uint8_t g = g1 + t*(g2-g1);
        uint8_t b = b1 + t*(b2-b1);
        fmt::print("\033[38;2;{};{};{}m{}",(ll)r,(ll)g,(ll)b,text[i]);
    }
    fmt::print("\033[0m\n");
}