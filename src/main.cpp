// 1. 必须放在最前面的宏定义
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

// 2. 强制 Windows 使用 ANSI 转义序列（Windows 10+ 已启用虚拟终端）
#define FORCE_ANSI_COLORS
#define TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES

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
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;
using namespace tabulate;

typedef long long ll;

#ifdef _WIN32
// 2. 必须先包含 winsock (因为你的项目用到了 curl)
#include <winsock2.h>
#include <windows.h>
#include <wincon.h> // 强制加载控制台 API
ll outputCodePage = GetConsoleOutputCP();
#endif

// 切换工作目录到程序自身所在文件夹
bool chdir_to_exe_dir()
{
    fs::path exe_path; // 定义在函数最外层，整个函数都能访问

#ifdef _WIN32
    // Windows 获取 exe 完整路径
    wchar_t buf[1024] = { 0 };
    GetModuleFileNameW(NULL, buf, 1024);
    exe_path = buf;
#else
    // Linux / macOS 获取程序路径
    char buf[PATH_MAX] = { 0 };
    ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
    if (len <= 0)
    {
        return false;
    }
    buf[len] = '\0';
    exe_path = std::string(buf);
#endif

    // 提取所在文件夹
    fs::path exe_dir = exe_path.parent_path();

    try
    {
        fs::current_path(exe_dir); // 切换工作目录
        return true;
    }
    catch (const std::exception& e)
    {
        return false;
    }
}


int main(){
    #if _WIN32
        SetConsoleOutputCP(CP_UTF8); // 设置控制台输出为 UTF-8 编码
        enableAnsiColor();
    #endif
    ios::sync_with_stdio(false); cin.tie(nullptr);
    chdir_to_exe_dir();
    set_title();
    print_title();
    check();
    string s=beautified_input("请输入要解析的项目ID",true);
    string resp=parse_modrinth(s);
    if(resp=="-1"){
        error_print("解析失败！");
        #if _WIN32
            SetConsoleOutputCP(outputCodePage); // 设置控制台输出为系统原编码
        #endif
        fakepause();
        return -1;
    }
    vector<map<string,string>> files=json2vec(parse(resp));
    if (files.size()==0)
    {
        warning_print("解析结果为空，请检查输入是否正确");
        error_print("解析失败辣！ゞ◎Д◎ヾ");
        #if _WIN32
            SetConsoleOutputCP(outputCodePage); // 设置控制台输出为系统原编码
        #endif
        fakepause();
        return 1;
    }
    #if _WIN32
    system(fmt::format("title MCParser v{} (r{}) - by {} - 已解析{}个文件",VERSION_STRING,GIT_HASH,AUTHOR,files.size()).c_str());
    #endif
    success_print(fmt::format("解析成功，共解析{}个文件\n",files.size()));
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
        .border_top("=")
        .border_bottom("=")
        .border_left("|")
        .border_right("|")
        .corner("+");
    filelist.add_row({"\033[1m索引\033[00m","\033[1m版本ID\033[00m","\033[1m版本名\033[00m","\033[1m发行时间\033[00m","\033[1m下载量\033[00m","\033[1m文件名\033[00m","\033[1m大小\033[00m","\033[1mMinecraft版本\033[00m"});
    for (ll i=0; i<limit; i++) {
        filelist.add_row(
            {
                files[i]["index"],
                files[i]["version_id"],
                files[i]["version_name"],
                files[i]["release_time"],
                files[i]["down"],
                files[i]["filename_display"],
                files[i]["size"],
                files[i]["mc_versions"]
            }
        );
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
    filelist.column(6).format()
        .font_color(Color::cyan);
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
    filelist[0][6].format()
        .font_color(Color::none);
    fmt::print("\033[3m文件列表（共{}个文件，已列出{}个）\033[0m\n",files.size(),limit);
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
        warning_print(fmt::format("输入范围超过{}，已自动设为0",files.size()-1));
        file_index=0;
    }
    string selected_url=files[file_index]["url"];
    string download_dir=beautified_input("请输入下载路径",true);
    info_print(fmt::format("正在下载 🌐 {} -> 📂 {}/{} ...",selected_url,download_dir,files[file_index]["filename"]));
    bool result=download_file(selected_url, download_dir+"/"+files[file_index]["filename"]);
    #if _WIN32
        SetConsoleOutputCP(outputCodePage); // 设置控制台输出为系统原编码
    #endif
    fakepause();
    if (result)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}