//������ͷ�ļ������е�include��ȫ�ֱ�������д������
//����дע�ͺ������ĺ�ϰ�ߣ����Լ�Ҳ�ñ��˿��ö�
//ע�ͣ���һ�к�һ��tab��//��ʼдע��
/*
����Ҳ��������д
����ע��
*/

//����Ϊ���ÿ�
#pragma once	//�Դ��Ĳ�����
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


using namespace std;

//����Ϊ���͡���������
//���г������д���»��ߣ�
#define MAIN_MENU_COUNT 13	//���˵�����
#define DATA_FILE "fs.dat"  //���ݿ��ļ�

//����ṹ��
typedef struct _fi_info //��֧��
{
    int year;
    int month;
    int type;       //1Ϊ���룬-1Ϊ֧��
    string name;    //��ͥ��Ա����������TA���������TA֧��
    float money;    //�����֧���Ľ��
    string detail;  //��ע��Ϣ
}fi_info;

struct FinanceItem
{
    int year=0;
    int month=0;
    int type=1;       //1Ϊ���룬-1Ϊ֧��
    string name="";    //��ͥ��Ա����������TA���������TA֧��
    float money=0;    //�����֧���Ľ��
    string detail="";  //��ע��Ϣ
};

//����Ϊȫ�ֱ�������
bool isinit=false;	//�����Ƿ��Ѿ���ʼ����ʶ��
vector<FinanceItem> FinanceBook;
bool issortincome=true;
bool issortrecent=true;


//������������
//!!�벻Ҫ�ڴ˶��庯����������鷳,����Ҫ������������


void initprogram();	//��ʼ������
void printmenu();	//��ӡ�˵�
void selectmenu();	//ѡ��˵�
void gotomenu(int menuno);	//��ת�˵�
void exitprogram();	//�˳�����

void clearFinanceItem(FinanceItem& item); //�����֧��

bool cmp(FinanceItem a, FinanceItem b);


void addincome();	//��������
void inputinfo(FinanceItem& financeinfo);  //�û�����������֧��Ŀ����
void inputquerycondition(FinanceItem& financeinfo);
void savetofile();  //д�뵽�ļ�
void getfromfile(); //���ļ���ȡ
void editincome();	//�༭����
void delincome();	//ɾ������

void addexpense();	//����֧��
void editexpense();	//�༭֧��
void delexpense();	//ɾ��֧��

void sortincome();	//��������
void sortexpense();	//����֧��

void queryincome();	//��ѯ����
void queryexpense();	//��ѯ֧��

void exporttable();	//�������

void editpassword();	//�༭��������
bool validatepassword(string pwd);	//��֤��������