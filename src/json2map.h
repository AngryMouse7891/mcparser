#ifndef JSON2MAP_H
#define JSON2MAP_H

#include <json/json.h>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include "convert.h"
#include "downloader.h"

Json::Value parse(std::string src);
std::vector<std::map<std::string,std::string>> json2vec(Json::Value src);

#endif