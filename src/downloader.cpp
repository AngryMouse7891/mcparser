#include <ios>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <curl/curl.h>
#include "termcolor/termcolor.hpp"
#include <fmt/format.h>
#include "print_beautify.h"
#include "certdir.h"
#include "downloader.h"

typedef long long ll;

// 进度回调函数
int progress_callback(void* clientp, 
                      curl_off_t dltotal, 
                      curl_off_t dlnow, 
                      curl_off_t ultotal, 
                      curl_off_t ulnow)
{
    if (dltotal > 0) {
        double progress = (double)dlnow / (double)dltotal * 100.0;
        int barWidth = 50;
        
        std::cout << "\r |" << termcolor::bold;
        ll pos = barWidth * dlnow / dltotal;
        for (ll i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << termcolor::yellow << "#";
            else if (i == pos) std::cout << "#";
            else std::cout << termcolor::white << "-";
        }
        std::cout << termcolor::reset << std::fixed << std::setprecision(2) << "| " << termcolor::green << progress << "%" << termcolor::cyan << " (" 
                  << 1.0*dlnow/1024 << "/" << 1.0*dltotal/1024 << " KB)         " << termcolor::reset;
        std::cout.flush();
    }
    return 0;
}

// 写入文件的回调函数
size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp)
{
    FILE* fp = (FILE*)userp;
    size_t written = fwrite(contents, size, nmemb, fp);
    return written;
}

bool download_file(std::string url, std::string output_path)
{
    CURL* curl = curl_easy_init();
    if (!curl) {
        error_print("初始化 CURL 失败");
        return false;
    }

    FILE* fp = fopen(output_path.c_str(), "wb");
    if (!fp) {
        error_print(fmt::format("无法创建文件: {}",output_path));
        curl_easy_cleanup(curl);
        return false;
    }

    // 设置 URL
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    
    // 写入文件
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    
    // 启用进度回调
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_callback);
    
    // 跟随重定向
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    // 指定证书文件路径
    curl_easy_setopt(curl, CURLOPT_CAINFO, get_cert_dir().c_str());
    
    // 执行下载
    CURLcode res = curl_easy_perform(curl);
    
    fclose(fp);
    curl_easy_cleanup(curl);
    
    fmt::print("\n");
    
    if (res != CURLE_OK) {
        error_print(fmt::format("下载失败: {}",curl_easy_strerror(res)));
        return false;
    }

    success_print("下载完成!");
    return true;
}
