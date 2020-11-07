
//����Ϊ���ÿ�
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

//����Ϊ���͡���������
#define MAIN_MENU_COUNT 13	//���˵�����
#define DATA_FILE "fs.dat"  //���ݿ��ļ���

//����ṹ��
struct FinanceItem
{
    int year=0;
    int month=0;
    int type=1;       //1Ϊ���룬-1Ϊ֧��
    string name="";    //��ͥ��Ա����������TA���������TA֧��
    double money=0;    //�����֧���Ľ��
    string detail="";  //��ע��Ϣ
};

//����Ϊȫ�ֱ�������
bool isinit=false;	//�����Ƿ��Ѿ���ʼ����ʶ��
vector<FinanceItem> FinanceBook;
bool issortincome=true; //�Ƿ���������
bool issortrecent=true; //�Ƿ�������������·�
bool issortnamefirst = false;   //�Ƿ�����������
bool issortbiggeramount = true; //�Ƿ�������������ǰ
int sysyear;    //��ǰϵͳ���
int sysmonth;   //��ǰϵͳ�·�


//������������

//������غ���
void initprogram();	//��ʼ������
void showabout();	//չʾ������Ļ
void exitprogram();	//�˳�����

//�˵��ຯ��
void printmenu();	//��ӡ�˵�
void selectmenu();	//ѡ��˵�
void gotomenu(int menuno);	//��ת�˵�

//�ײ㹦���ຯ��
string gettimestr(tm t, int mode);  //��ȡ��ǰʱ���ַ���
void clearFinanceItem(FinanceItem& item); //�����֧��
bool cmp(FinanceItem a, FinanceItem b); //�ṹ��������
bool isNameLegal(string name,bool isallowstarmark=false);   //�ж������Ƿ�Ϸ�
void savetofile();  //д�뵽�ļ�
void getfromfile(); //���ļ���ȡ
void exporttofile(vector<FinanceItem> queryresult, double sum,tm t);

//�û������ຯ��
void inputinfo(FinanceItem& financeinfo);  //�û�����������֧��Ŀ����
void inputquerycondition(FinanceItem& financeinfo);  //�û����������ѯ��������

//���幦�ܺ���
void addincome();	//��������
void editincome();	//�༭����
void delincome();	//ɾ������

void addexpense();	//����֧��
void editexpense();	//�༭֧��
void delexpense();	//ɾ��֧��

void setsortrecent();	//�����Ƿ�������������·�
void setsortbiggeramount();	//�����Ƿ�������������ǰ

void queryincome();	//��ѯ����
void queryexpense();//��ѯ֧��

void exporttable();	//�������

