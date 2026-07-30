#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <ios>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <curl/curl.h>
#include "termcolor/termcolor.hpp"
#include <fmt/format.h>
#include "print_beautify.h"
#include "certdir.h"
#include "convert.h"

typedef long long ll;

// 辅助函数：将字节数转换为人类可读的字符串 (KB, MB, GB)
std::string formatSize(double src_bytes);

// 辅助函数：将秒数转换为 HH:MM:SS 格式
std::string formatTime(double seconds);

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