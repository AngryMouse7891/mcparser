#ifndef UPDCHECK_H
#define UPDCHECK_H

#include <json/value.h>
#include <curl/curl.h>
#include <json/json.h>
#include <fmt/base.h>
#include <iostream>
#include <string>
#include <vector>
#include "version.h"
#include "parser.h"
#include "json2map.h"
#include "termcolor/termcolor.hpp"
#include "print_beautify.h"
#include "certdir.h"
#include "spilt.h"

std::string get_releases();
std::string islatest();
void check();

#endif