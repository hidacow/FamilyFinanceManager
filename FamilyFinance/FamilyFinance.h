
//以下为引用库
#pragma once
#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstdio>
#include<string>
#include<ctime>
#include<cctype>
#include<vector>
#include<fstream>
#include<assert.h>
#include<algorithm>
#include<sstream>

using namespace std;

//以下为类型、常量定义
#define MAIN_MENU_COUNT 13	//主菜单项数
#define DATA_FILE "fs.dat"  //数据库文件名

//定义结构体
struct FinanceItem
{
    int year=0;
    int month=0;
    int type=1;       //1为收入，-1为支出
    string name="";    //家庭成员姓名，属于TA的收入或由TA支出
    double money=0;    //收入或支出的金额
    string detail="";  //备注信息
};

//以下为全局变量定义
bool isinit=false;	//程序是否已经初始化标识符
vector<FinanceItem> FinanceBook;
bool issortincome=true; //是否先排收入
bool issortrecent=true; //是否先排最近的年月份
bool issortnamefirst = false;   //是否先排序名字
bool issortbiggeramount = true; //是否数额更大的项在前
int sysyear;    //当前系统年份
int sysmonth;   //当前系统月份


//以下声明函数

//程序相关函数
void initprogram();	//初始化程序
void showabout();	//展示关于屏幕
void exitprogram();	//退出程序

//菜单类函数
void printmenu();	//打印菜单
void selectmenu();	//选择菜单
void gotomenu(int menuno);	//跳转菜单

//底层功能类函数
string gettimestr(tm t, int mode);  //获取当前时间字符串
void clearFinanceItem(FinanceItem& item); //清空收支项
bool cmp(FinanceItem a, FinanceItem b); //结构体排序函数
bool isNameLegal(string name,bool isallowstarmark=false);   //判断名字是否合法
void savetofile();  //写入到文件
void getfromfile(); //从文件读取
void exporttofile(vector<FinanceItem> queryresult, double sum,tm t);

//用户输入类函数
void inputinfo(FinanceItem& financeinfo);  //用户交互输入收支项目函数
void inputquerycondition(FinanceItem& financeinfo);  //用户交互输入查询条件函数

//具体功能函数
void addincome();	//增加收入
void editincome();	//编辑收入
void delincome();	//删除收入

void addexpense();	//增加支出
void editexpense();	//编辑支出
void delexpense();	//删除支出

void setsortrecent();	//设置是否先排最近的年月份
void setsortbiggeramount();	//设置是否数额更大的项在前

void queryincome();	//查询收入
void queryexpense();//查询支出

void exporttable();	//导出表格

