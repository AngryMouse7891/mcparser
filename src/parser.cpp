#include <curl/curl.h>
#include <fmt/format.h>
#include <iostream>
#include <string>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string parse_modrinth(std::string project_id){
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();

    std::string url=fmt::format("https://api.modrinth.com/v2/project/{0}/version",project_id);

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
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