#include <string>

#include "mirror.h"

using namespace std;

string replaceModrinthFilesMirror(string src){
    return src.replace(8,16,"mod.mcimirror.top");
}