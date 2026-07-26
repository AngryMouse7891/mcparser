#include <json/value.h>
#include <curl/curl.h>
#include <json/json.h>
#include <fmt/base.h>
#include <iostream>
#include <string>
#include "version.h"
#include "parser.h"
#include "json2map.h"
#include "termcolor/termcolor.hpp"
#include "print_beautify.h"
#include "certdir.h"

std::string get_releases(){
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://gitee.com/api/v5/repos/AngryMouse7891/mcparser/releases/latest");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json;charset=UTF-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        // 可选：设置超时时间（单位：毫秒）
        curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 10000L);
        // 指定证书文件路径
        curl_easy_setopt(curl, CURLOPT_CAINFO, get_cert_dir().c_str());

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            error_print(fmt::format("GET request failed: {}",curl_easy_strerror(res)));
            readBuffer.clear();
            return "-1";
        }

        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

std::string islatest(){
    std::string stat=get_releases();
    if (stat=="-1") {
        return "-1"; //更新检测失败
    }
    Json::Value releases=parse(stat);
    if (releases["tag_name"].asString()<=VERSION_STRING) {
        return "0";
    } else {
        return releases["tag_name"].asString();
    }
}

void check(){
    fmt::print("[更新检测] 正在检查更新...\n");
    std::string res=islatest();
    if (res=="0") {
        success_print(fmt::format("已是最新版（{}）\n",VERSION_STRING));
    } else if (res=="-1") {
        error_print("更新检查失败");
    } else {
        std::string prompt_str=fmt::format("发现新版本！{} -> {}请去以下下载渠道下载更新：\nGitee Releases（可下载Windows、Linux版以及源代码）：https://gitee.com/AngryMouse7891/mcparser/releases\n夸克网盘（仅Windows版）：https://pan.quark.cn/s/f88f5aed5752\n百度网盘（可下载Windows、Linux版，提取码`bikb`）：https://pan.baidu.com/s/1-WTiixGq7kUxkVbkALO_Ew\n",
            VERSION_STRING,res);
        info_print(prompt_str);
    }
}