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
#include "downloader.h"

typedef long long ll;

// 辅助函数：将字节数转换为人类可读的字符串 (KB, MB, GB)
std::string formatSize(double src_bytes) {
    const char* suffixes[] = {"B", "KiB", "MiB", "GiB", "TiB"};
    int suffixIndex = 0;
    while (src_bytes >= 1024 && suffixIndex < 4) {
        src_bytes /= 1024;
        suffixIndex++;
    }
    
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%.2f %s", src_bytes, suffixes[suffixIndex]);
    return std::string(buffer);
}

// 辅助函数：将秒数转换为 HH:MM:SS 格式
std::string formatTime(double seconds) {
    if (seconds < 0) return "--'--\"";
    
    int mins = ((int)seconds % 3600) / 60;
    int secs = (int)seconds % 60;
    
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%02d'%02d\"", mins, secs);
    return std::string(buffer);
}

// 进度回调函数
int progress_callback(void* clientp, 
                      curl_off_t dltotal, 
                      curl_off_t dlnow, 
                      curl_off_t ultotal, 
                      curl_off_t ulnow)
{
    CURL* curl = (CURL*)clientp;
    
    if (dltotal > 0) {
        double progress = (double)dlnow / (double)dltotal * 100.0;
        int barWidth = 50;

        // 获取平均下载速度
        double speed = 0.0;
        curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &speed);

        // 计算剩余时间
        double time_remaining = 0.0;
        if (speed > 0) {
            time_remaining = (dltotal - dlnow) / speed;
        }
        std::cout << "\r";
        ll pos = barWidth * dlnow / dltotal;
        std::cout<<termcolor::green << ll(progress) << "% ";
        for (ll i = 0; i < barWidth; ++i) {
            if (i <= pos) std::cout << termcolor::blue << "█";
            else std::cout << termcolor::grey << "█";
        }
        std::cout << termcolor::reset << std::fixed << std::setprecision(2) << " " << termcolor::cyan << " (" 
                  << formatSize(dlnow) << "/" << formatSize(dltotal) << ") " << termcolor::magenta << formatSize(speed) << "/s " 
                  << termcolor::yellow << formatTime(time_remaining) << "     " << termcolor::reset;
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
    
    curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, curl);

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
