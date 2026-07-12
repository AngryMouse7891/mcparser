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
#include "updcheck.h"
#include "termcolor/termcolor.hpp"

using namespace std;
using namespace tabulate;

typedef long long ll;

#ifdef _WIN32
#include <windows.h>
ll outputCodePage = GetConsoleOutputCP();
#endif

int main(){
    #if _WIN32
        SetConsoleOutputCP(CP_UTF8); // 设置控制台输出为 UTF-8 编码
    #endif
    print_title();
    check();
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
    ll limit=0;
    if(show_limit1==""){
        limit=5;
    }else if(show_limit1=="0"){
        show_limit1=files.size();
    }else{
        limit=stoll(show_limit1);
    }
    string resp=parse_modrinth(s);
    if(resp=="-1"){
        cout<<termcolor::red<<"解析失败"<<termcolor::reset<<'\n';
        fakepause();
        return 1;
    }
    for (ll i=0; i<limit; i++) {
        filelist.add_row({files[i]["index"],files[i]["version_id"],files[i]["version_name"],files[i]["release_time"],files[i]["down"],files[i]["filename"]});
    } 
    cout<<filelist<<'\n';
    string file_index_input=beautified_input("请输入要下载的文件索引（留空则默认为0）");
    ll file_index=0;

    if (file_index_input==""){
        file_index=0;
    }else{
        file_index=stoll(file_index_input);
    }
    string selected_url=files[file_index]["url"];
    string download_dir=beautified_input("请输入下载路径");
    fmt::print("正在下载{}...\n",selected_url);
    download_file(selected_url, download_dir+"/"+files[file_index]["filename"]);
    fmt::print("\n");
    #if _WIN32
        SetConsoleOutputCP(outputCodePage); // 设置控制台输出为系统原编码
    #endif
    fmt::print("\n");
    fakepause();
    return 0;
}