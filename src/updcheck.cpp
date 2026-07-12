#include <json/value.h>
#include <curl/curl.h>
#include <json/json.h>
#include <fmt/color.h>
#include <fmt/base.h>
#include <iostream>
#include <string>
#include "version.h"
#include "parser.h"
#include "json2map.h"
#include "termcolor/termcolor.hpp"

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
        curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 5000L);
        // 指定证书文件路径
        curl_easy_setopt(curl, CURLOPT_CAINFO, "cacert.pem");

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "GET request failed: " << curl_easy_strerror(res) << std::endl;
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
        std::cout<<termcolor::green<<"[✅] 已是最新版\n"<<termcolor::reset;
    } else if (res=="-1") {
        std::cout<<termcolor::red<<"[❌] 更新检查失败\n"<<termcolor::reset;
    } else {
        std::cout<<termcolor::yellow<<fmt::format("[⚠] 发现新版本！{} -> {}\n请去https://gitee.com/AngryMouse7891/mcparser/releases或https://pan.quark.cn/s/f88f5aed5752下载更新。\n",VERSION_STRING,res)<<termcolor::reset;
    }
}