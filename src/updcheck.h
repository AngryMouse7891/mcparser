#ifndef UPDCHECK_H
#define UPDCHECK_H

#include "json/value.h"
#include <curl/curl.h>
#include <json/json.h>
#include <fmt/color.h>
#include <fmt/base.h>
#include <fmt/format.h>
#include <iostream>
#include <string>
#include "version.h"
#include "parser.h"
#include "termcolor/termcolor.hpp"

std::string get_releases();
Json::Value parse_json(std::string src);
std::string islatest();
void check();

#endif