//这里是头文件，所有的include和全局变量声明写在这里
//养成写注释和缩进的好习惯，让自己也让别人看得懂
//注释：在一行后按一次tab打//开始写注释
/*
或者也可以这样写
多行注释
*/

//以下为引用库
#pragma once	//自带的不管它
#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cctype>
using namespace std;
//以下为类型、常量定义
//所有常量请大写加下划线！
#define MAIN_MENU_COUNT 13	//主菜单项数


//以下为全局变量定义
bool isinit;	//程序是否已经初始化标识符


//以下声明函数
//!!请不要在此定义函数以免造成麻烦,但是要在这里声明！


void initprogram();	//初始化程序
void printmenu();	//打印菜单
void selectmenu();	//选择菜单
void gotomenu(int menuno);	//跳转菜单
void exitprogram();	//退出程序

void addincome();	//增加收入
void editincome();	//编辑收入
void delincome();	//删除收入

void addexpense();	//增加支出
void editexpense();	//编辑支出
void delexpense();	//删除支出

void sortincome();	//排序收入
void sortexpense();	//排序支出

void queryincome();	//查询收入
void queryexpense();	//查询支出

void exporttable();	//导出表格

void editpassword();	//编辑操作密码
bool validatepassword(string pwd);	//验证操作密码


