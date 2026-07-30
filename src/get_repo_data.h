#ifndef GET_REPO_DATA_H
#define GET_REPO_DATA_H

#include <curl/curl.h>
#include <string>
#include <map>
#include <json/json.h>
#include <fmt/format.h>
#include "json2map.h"
#include "print_beautify.h"
#include "certdir.h"
#include "parser.h"
#include "gradient.h"

std::string get_repo_data();

std::map<std::string,int> convert_data(std::string src);

void print_data();

#endif