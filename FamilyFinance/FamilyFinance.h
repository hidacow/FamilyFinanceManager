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
#include<cstring>
#include<ctime>
#include<cctype>
using namespace std;
//����Ϊ���͡���������
//���г������д���»��ߣ�
#define MAIN_MENU_COUNT 13	//���˵�����


//����Ϊȫ�ֱ�������
bool isinit;	//�����Ƿ��Ѿ���ʼ����ʶ��


//������������
//!!�벻Ҫ�ڴ˶��庯����������鷳,����Ҫ������������


void initprogram();
void printmenu();
void gotomenu(int menuno);
void exitprogram();

void addincome();
void editincome();
void delincome();


