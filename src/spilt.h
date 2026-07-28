#include <sstream>
#include <vector>
#include <string>

using namespace std;

vector<string> spiltstr(string src,char c){
    stringstream ss(src.c_str()); // 将字符数组转换为字符串流
    vector<string> result;
    string token;

    // 使用 getline 按逗号分割
    while (getline(ss, token, c)) {
        result.push_back(token);
    }

    return result;
}

vector<int> to_number(vector<string> src){
    vector<int> res;
    for (size_t i = 0; i < src.size(); i++)
    {
        res.push_back(stoi(src[i]));
    }
    return res;
}