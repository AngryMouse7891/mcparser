#include "termcolor/termcolor.hpp"
#include <iostream>
#include "version.h"

using namespace std;

void print_title(){
    cout<<termcolor::on_blue<<"                                                              "<<termcolor::reset<<'\n';
    cout<<termcolor::on_blue<<"=============================================================="<<termcolor::reset<<'\n';
    cout<<termcolor::on_blue<<"                                                              "<<termcolor::reset<<'\n';
    cout<<termcolor::on_blue<<"MCParser  "<<VERSION_STRING<<"                                               "<<termcolor::reset<<'\n';
    cout<<termcolor::on_blue<<"                                                              "<<termcolor::reset<<'\n';
    cout<<termcolor::on_blue<<"https://gitee.com/AngryMouse7891/mcparser/                    "<<termcolor::reset<<'\n';
    cout<<termcolor::on_blue<<"                                                              "<<termcolor::reset<<'\n';
    cout<<termcolor::on_blue<<"=============================================================="<<termcolor::reset<<'\n';
    cout<<termcolor::on_blue<<"                                                              "<<termcolor::reset<<"\n\n";
}