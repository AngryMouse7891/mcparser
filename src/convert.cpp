#include <json/json.h>
#include <string>
#include <cmath>
#include <chrono>
#include <ctime>
#include <sstream>
#include "convert.h"

using namespace std;
using namespace chrono;

string jsonarray2str(Json::Value src, int limit){
    // 创建字符串流来保存数组内容
    stringstream ss;

    int cnt=0;
        
    // 遍历数组元素
    for (const auto& item : src) {
        // 将每个元素转换为字符串并添加到结果中
        if (item.isString()) {
            ss << item.asString() << ", ";
        } else if (item.isInt()) {
            ss << item.asInt() << ", ";
        } else if (item.isBool()) {
            ss << (item.asBool() ? "true" : "false") << ", ";
        } else if (item.isDouble()) {
            ss << item.asDouble() << ", ";
        } else if (item.isNull()) {
            ss << "null, ";
        }
        cnt++;
        if (cnt>=limit)
        {
            break;
        }
        // 其他类型可以根据需要添加
    }

    // 获取最终字符串
    string res = ss.str();
    res.pop_back(); res.pop_back();
    if (src.size()>=limit)
    {
        res+=" (+";
        res+=to_string(src.size()-limit);
        res+=')';
    }
    return res;
}

double round_k(double x, int k) {
    double pow10 = pow(10, k);
    return round(x * pow10) / pow10;
}

// ISO8601 UTC 解析函数
string convert_time(const string& iso_str)
{
    // 1. 解析 ISO8601 UTC: 2026-06-29T18:09:03.301428Z
    system_clock::time_point tp;
    istringstream iss(iso_str);
    iss >> parse("%FT%TZ", tp);

    // 2. 截断到秒，彻底丢掉微秒/纳秒
    auto tp_second = floor<seconds>(tp);

    // 3. system_clock -> time_t
    time_t sec = system_clock::to_time_t(tp_second);

    // 4. gmtime = UTC时间！重点！不要用localtime
    tm utc_tm = *gmtime(&sec);

    // 5. 格式化输出：2026-06-29 18:09:03
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &utc_tm);
    return buf;
}