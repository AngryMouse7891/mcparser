#include <iostream>
#include <windows.h>

void fakepause() {
    #if _WIN32
    system("pause");
    #endif
}