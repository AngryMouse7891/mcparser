#include <iostream>
#if _WIN32
#include <windows.h>
#endif
#include "fakepause.h"

void fakepause() {
    #if _WIN32
    system("pause");
    #endif
}