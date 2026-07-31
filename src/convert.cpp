#include <json/json.h>
#include <string>
#include <cmath>
#include "convert.h"

using namespace std;

string jsonarray2str(Json::Value src){
    // 创建字符串流来保存数组内容
    stringstream ss;
        
    // 遍历数组元素
    for (const auto& item : src) {
        // 将每个元素转换为字符串并添加到结果中
        if (item.isString()) {
            ss << item.asString() << ",";
        } else if (item.isInt()) {
            ss << item.asInt() << ",";
        } else if (item.isBool()) {
            ss << (item.asBool() ? "true" : "false") << ",";
        } else if (item.isDouble()) {
            ss << item.asDouble() << ",";
        } else if (item.isNull()) {
            ss << "null,";
        }
        // 其他类型可以根据需要添加
    }

    // 获取最终字符串
    string res = ss.str();
    res.push_back();
    return res;
}

double round_k(double x, int k) {
    double pow10 = pow(10, k);
    return round(x * pow10) / pow10;
}