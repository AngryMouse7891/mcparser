#include <json/json.h>
#include <sstream>
#include <vector>
#include <map>
#include <string>

Json::Value parse(std::string src){
    // 新版推荐解析器
    Json::CharReaderBuilder reader_builder;
    std::string err_msg;
    Json::Value root;
    std::istringstream iss(src);
    // 解析字符串
    bool ok = Json::parseFromStream(
        reader_builder,
        iss,
        &root,
        &err_msg
    );

    return root;
}

std::vector<std::map<std::string,std::string>> json2vec(Json::Value src){
    std::vector<std::map<std::string,std::string>> res;
    for(int i=0; i<src.size(); i++) {
        /*std::map<std::string,std::string> tmp={
            {"index",std::to_string(i)},
            {"version_id",src[i]["id"]},
            {"version_name",src[i]["name"]},
            {"release_time",src[i]["date_published"]},
            {"down",src[i]["downloads"].asString()},
            {"filename",src[i]["files"][0]["filename"]},
            {"url",src[i]["files"][0]["url"]}
        };*/
        /*tmp["index"]=std::to_string(i);
        tmp["version_id"]=src[i]["id"];
        tmp["version_name"]=src[i]["name"];
        tmp["release_time"]=src[i]["date_published"];
        tmp["down"]=std::to_string(src[i]["downloads"]);
        tmp["filename"]=src[i]["files"][0]["filename"];
        tmp["url"]=src[i]["files"][0]["url"];*/
        res.push_back(
            {
                {"index",std::to_string(i)},
                {"version_id",src[i]["id"].asString()},
                {"version_name",src[i]["name"].asString()},
                {"release_time",src[i]["date_published"].asString()},
                {"down",src[i]["downloads"].asString()},
                {"filename",src[i]["files"][0]["filename"].asString()},
                {"url",src[i]["files"][0]["url"].asString()}
            }
        );
    }
    return res;
}