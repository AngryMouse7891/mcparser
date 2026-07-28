#ifndef TITLE_H
#define TITLE_H

#include "termcolor/termcolor.hpp"
#include <iostream>
#include <fmt/format.h>
#include <fmt/base.h>
#include "version.h"
#include "gradient.h"
#include "splashes.h"
#if _WIN32
#include <windows.h>
#endif


using namespace std;

void set_title();

void print_title();

#endif