#ifndef PARSER_H
#define PARSER_H

#include <curl/curl.h>
#include <fmt/format.h>
#include <iostream>
#include <string>
#include "termcolor/termcolor.hpp"
#include "print_beautify.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
std::string parse_modrinth(std::string project_id);

#endif