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


void initprogram();	//��ʼ������
void printmenu();	//��ӡ�˵�
void selectmenu();	//ѡ��˵�
void gotomenu(int menuno);	//��ת�˵�
void exitprogram();	//�˳�����

void addincome();	//��������
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


