#include <curl/curl.h>
#include <fmt/format.h>
#include <iostream>
#include <string>
#include "termcolor/termcolor.hpp"
#include "print_beautify.h"
#include "certdir.h"
#include "parser.h"
#include "version.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string parse_modrinth(std::string project_id){
    CURL* curl;
    CURLcode res;
    long http_code = 0;
    std::string readBuffer;

    curl = curl_easy_init();

    std::string url=fmt::format("https://mod.mcimirror.top/modrinth/v2/project/{}/version",project_id);

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, fmt::format("User-Agent: AngryMouse7891/mcparser/{}",VERSION_STRING).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        // 可选：设置超时时间（单位：毫秒）
        curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 30000L);
        // 指定证书文件路径
        curl_easy_setopt(curl, CURLOPT_CAINFO, get_cert_dir().c_str());


        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        }

        if (res != CURLE_OK) {
            error_print(fmt::format("GET request failed: {}",curl_easy_strerror(res)));
            readBuffer.clear();
            return "-1";
        }

        curl_easy_cleanup(curl);
    }
    if (http_code >= 400) {
        return "-1";
    }
    return readBuffer;
}