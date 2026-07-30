#include "get_repo_data.h"
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

std::string get_repo_data(){
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://gitee.com/api/v5/repos/AngryMouse7891/mcparser");
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

std::map<std::string,int> convert_data(std::string src){
    Json::Value parsed=parse(src);
    std::map<std::string,int> res={
        {"forks",parsed["forks_count"].asInt()},
        {"stars",parsed["stargezers_count"].asInt()},
        {"open_issues",parsed["open_issues_count"].asInt()}
    };
    return res;
}

void print_data(){
    std::string fetched=get_repo_data();
    if (fetched=="-1")
    {
        error_print("仓库数据获取失败");
        return;
    }
    std::map<std::string,int> repo_data=convert_data(fetched);
    std::string msg=fmt::format("{} stars | {} forks | {} open issues",repo_data["forks"],repo_data["stars"],repo_data["open_issues"]);
    printGradientRGB(msg,214,236,240,179,92,68);
}