#include <iostream>
#include <limits>   // numeric_limits

void fakepause() {
    std::cout << "Press Enter to continue..." << std::endl;
    // 清空输入缓冲区残留，然后等待回车
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
}