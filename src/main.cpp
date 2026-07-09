#include <aria2/aria2.h>
#include <fmt/base.h>
#include <bits/stdc++.h>
#include <vector>
#include <map>
#include <string>
#include "input_beautify.h"
#include "parser.h"
#include "title.h"
#include "json2map.h"
#include "fakepause.h"
#include "tabulate/table.hpp"
#include "downloader.h"
#include "termcolor/termcolor.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;
using namespace tabulate;

typedef long long ll;

#if _WIN32
int outputCodePage = GetConsoleOutputCP();
#endif

int main(){
    if (_WIN32) {
        SetConsoleOutputCP(CP_UTF8); // 设置控制台输出为 UTF-8 编码
    }
    print_title();
    string s=beautified_input("请输入要解析的项目ID");
    Table filelist;
    filelist.format()
        .font_style({FontStyle::bold}) // 表头加粗
        .border_top("=")
        .border_bottom("=")
        .border_left("|")
        .border_right("|")
        .corner("+");
    filelist.add_row({"索引","版本ID","版本名","发行时间","下载量","文件名"});
    string res=parse_modrinth(s);
    vector<map<string,string>> files=json2vec(parse(res));
    string show_limit1=beautified_input("请输入最多展示几条（0为所有，留空则默认为5）");
    int limit=0;
    if(show_limit1==""){
        limit=5;
    }else if(show_limit1=="0"){
        show_limit1=files.size();
    }else{
        limit=stoi(show_limit1);
    }
    string resp=parse_modrinth(s);
    if(resp=="-1"){
        cout<<termcolor::red<<"解析失败"<<termcolor::reset<<'\n';
        fakepause();
        return 1;
    }
    for (int i=0; i<limit; i++) {
        filelist.add_row({files[i]["index"],files[i]["version_id"],files[i]["version_name"],files[i]["release_time"],files[i]["down"],files[i]["filename"]});
    } 
    cout<<filelist<<'\n';
    string file_index_input=beautified_input("请输入要下载的文件索引（留空则默认为0）");
    int file_index=0;

    if (file_index_input==""){
        file_index=0;
    }else{
        file_index=stoi(file_index_input);
    }
    string selected_url=files[file_index]["url"];
    string download_dir=beautified_input("请输入下载路径");
    cout<<"正在下载"<<selected_url<<"...\n";
    download_file(selected_url, download_dir+"/"+files[file_index]["filename"]);
    cout<<'\n';
    if (_WIN32) {
        SetConsoleOutputCP(outputCodePage); // 设置控制台输出为 UTF-8 编码
    }
    cout<<'\n';
    fakepause();
    return 0;
}