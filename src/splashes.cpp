#include<random>
#include<iostream>
#include<vector>
#include<string>
#include "splashes.h"

using namespace std;

vector<string> splashes={
    "Open source on Gitee!",
    "MCParser = MalfunctionCraft Parser (bushi",
    "Give a star!",
    "Did you want to open a pull request?",
    "Sorry, only for Modrinth.",
    "作者mcbbs纪念版已经lv3了",
    "秦始皇骑北极熊，北极熊骑秦始皇",
    "提个issue吧求求了",
    "100% Writen with using C++!",
    "无 敌 神 镐",
    "！？强强？！",
    "无 敌 玄 素 镐",
    "特辣的海藻！！！🔥🔥🔥",
    "未曾设想的道路",
    "八月白露降，槐叶次第黄。 ————【唐】白居易《和答诗十首·和松树》",
    "立 入 禁 止",
    "两 只 老 虎 爱 跳 舞 ~"
};

int randint(int mininum,int maxinum){
    random_device rd;
    mt19937 gen(rd()); 
    uniform_int_distribution<> distrib(mininum, maxinum); 
    return distrib(gen);
}

string rand_splash(){
    return splashes[randint(0,splashes.size()-1)];
}