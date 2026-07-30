#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#define WIN32_LEAN_AND_MEAN // 排除极少使用的 Windows 服务，加快编译，减少冲突
#define NOMINMAX            // 防止 Windows 宏污染 min/max 函数
#include <ios>
#if _WIN32
#include <winsock2.h>
#include <windows.h> 
#include <wincon.h> // 强制加载控制台 API
#endif
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <curl/curl.h>
#include "termcolor/termcolor.hpp"
#include <fmt/format.h>
#include "print_beautify.h"
#include "certdir.h"

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