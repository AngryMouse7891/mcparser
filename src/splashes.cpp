#include<random>
#include<iostream>
#include<vector>
#include<string>

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
    "100% Writen with using C++!"
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