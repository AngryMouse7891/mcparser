#include <fmt/base.h>
#include <iostream>
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
#include "tabulate/color.hpp"
#include "gradient.h"
#include "print_beautify.h"

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
        SetConsoleCP(CP_UTF8);
        enableAnsiColor();
    #endif
    ios::sync_with_stdio(false); cin.tie(nullptr);
    set_title();
    print_title();
    check();
    string s=beautified_input("请输入要解析的项目ID");
    string resp=parse_modrinth(s);
    if(resp=="-1"){
        error_print("解析失败");
        #if _WIN32
            SetConsoleOutputCP(outputCodePage); // 设置控制台输出为系统原编码
            SetConsoleCP(outputCodePage);
        #endif
        fakepause();
        return 1;
    }
    vector<map<string,string>> files=json2vec(parse(resp));
    success_print(fmt::format("[✅] 解析成功，共解析{}个文件\n",files.size()));
    string show_limit1=beautified_input("请输入最多展示几条（0或`all`为所有，留空则默认为5）");
    ll limit=0;
    if(show_limit1.empty()){
        limit=5;
    }else if(show_limit1=="0" || show_limit1=="all"){
        limit=files.size();
    }else{
        limit=stoll(show_limit1);
    }
    if (limit>files.size())
    {
        warning_print(fmt::format("输入范围超过{}，已自动设为{}",files.size(),files.size()));
        limit=files.size();
    }
    Table filelist;
    filelist.format()
        .font_style({FontStyle::bold}) // 表头加粗
        .border_top("=")
        .border_bottom("=")
        .border_left("|")
        .border_right("|")
        .corner("+");
    filelist.add_row({"索引","版本ID","版本名","发行时间","下载量","文件名"});
    for (ll i=0; i<limit; i++) {
        filelist.add_row({files[i]["index"],files[i]["version_id"],files[i]["version_name"],files[i]["release_time"],files[i]["down"],files[i]["filename"]});
    } 
    filelist.column(0).format()
        .font_color(Color::cyan);
    filelist.column(1).format()
        .font_color(Color::magenta);
    filelist.column(2).format()
        .font_color(Color::green);
    filelist.column(3).format()
        .font_color(Color::blue);
    filelist.column(4).format()
        .font_color(Color::yellow);
    filelist.column(5).format()
        .font_color(Color::red);
    filelist[0][0].format()
        .font_color(Color::none);
    filelist[0][1].format()
        .font_color(Color::none);
    filelist[0][2].format()
        .font_color(Color::none);
    filelist[0][3].format()
        .font_color(Color::none);
    filelist[0][4].format()
        .font_color(Color::none);
    filelist[0][5].format()
        .font_color(Color::none);
    fmt::print("文件列表（共{}个文件，已列出{}个）\n",files.size(),limit);
    cout<<filelist<<'\n';
    string file_index_input=beautified_input("请输入要下载的文件索引（留空则默认为0）");
    ll file_index=0;
    if (file_index_input.empty()){
        file_index=0;
    }else{
        file_index=stoll(file_index_input);
    }
    if (file_index>=files.size())
    {
        warning_print(fmt::format("输入范围超过{}，已自动设为{}",files.size()-1,files.size()-1));
        file_index=files.size()-1;
    }
    string selected_url=files[file_index]["url"];
    string download_dir=beautified_input("请输入下载路径");
    info_print(fmt::format("正在下载{}...\n",selected_url));
    download_file(selected_url, download_dir+"/"+files[file_index]["filename"]);
    fmt::print("\n");
    #if _WIN32
        SetConsoleOutputCP(outputCodePage); // 设置控制台输出为系统原编码
        SetConsoleCP(outputCodePage);
    #endif
    fmt::print("\n");
    fakepause();
    return 0;
}