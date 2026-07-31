#include "format_number.h"
#include <cstdio>
#include <string>
#include <vector>
#include "convert.h"

typedef long long ll;

std::string formatNum(int num){
    if (num<10000)
    {
        return to_string(num);
    }
    double numd=num;
    std::vector<std::string> suffixes = {"", "万", "亿", "兆", "京"};
    int suffixIndex = 0;
    while (numd >= 10000 && suffixIndex < suffixes.size()) {
        numd /= 1.0*10000;
        suffixIndex++;
    }
    
    std::string res;
    std::ostringstream numStream;
    numStream << round_k(numd,1);
    res+=numStream.str();
    res+=suffixes[suffixIndex];
    return res;
}
