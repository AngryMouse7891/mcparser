#include <iostream>
#if _WIN32
#include <windows.h>
#endif

void fakepause() {
    #if _WIN32
    system("pause");
    #endif
}