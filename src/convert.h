#include <json/json.h>
#include <string>
#include <cmath>
#include <chrono>
#include <format>
#include <ctime>

using namespace std;
using namespace chrono;

string jsonarray2str(Json::Value src, int limit);

double round_k(double x, int k);

// ISO8601 UTC 解析函数
string convert_time(const string& iso_str);