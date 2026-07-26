#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <ios>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <curl/curl.h>
#include "termcolor/termcolor.hpp"
#include <fmt/format.h>
#include "print_beautify.h"
#include "certdir.h"

typedef long long ll;

// 进度回调函数
int progress_callback(void* clientp, 
                      curl_off_t dltotal, 
                      curl_off_t dlnow, 
                      curl_off_t ultotal, 
                      curl_off_t ulnow);

// 写入文件的回调函数
size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp);

bool download_file(std::string url, std::string output_path);

#endif