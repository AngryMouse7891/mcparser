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
    "两 只 老 虎 爱 跳 舞 ~",
    "得吃了😋😋😋",
    "写的什么玩意这是！！！(╯▔皿▔)╯",
    "庭中有奇树，绿叶发华兹。 ————【两汉】《古诗十九首》",
    "我报路长嗟日暮，学诗谩有惊人句。九万里风鹏正举。风休住，蓬舟吹取三山去！ ————【宋】李清照《渔家傲·天接云涛连晓雾》",
    "Creeper?",
    "aww man",
    "大狗大狗叫叫叫🐶🐶🐶",
    "Hello, I'm Verity! Your personal helper friend. Ask me everything, I know everything.",
    "666磕到甲沟炎了",
    "牛来",
    "你为什么不去问问神奇海螺呢？",
    "gogogo出发咯",
    "Ciallo～(∠・ω・)⌒☆",
    "MkDocs update!",
    "MkDocs+Material for MkDocs, YYDS!",
    "眼睛瞎在手机上",
    "⚡ Gotta Go Fast! 🔵",
    "囊囊囊囊囊囊囊~",
    "闯关弟子注意，本关考验你听声辩位功夫",
    "我命由我不由天！！！",
    "🍉吃瓜群众 请围观🍉",
    "头 脑 风 暴",
    "再见，暑假(ノへ￣、)"
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