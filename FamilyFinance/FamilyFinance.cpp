// FamilyFinance.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//养成写注释和缩进的好习惯，让自己也让别人看得懂
//注释：在一行后按一次tab打//开始写注释
/*
或者也可以这样写
多行注释
*/

#include "FamilyFinance.h"  //调用头文件
using namespace std;

int main()
{
    int selection;
    initprogram();  //初始化程序
    while (true)
    {
        system("cls");  //清屏
        printmenu();    //打印主菜单
        cout << "请选择菜单 [1-" << MAIN_MENU_COUNT << "]:";
        selection = 0;
        cin >> selection;
        if (cin.fail() || selection<1 || selection > MAIN_MENU_COUNT)
        {
            cout << "输入错误！"<<endl;
            system("pause");    //让用户按任意键继续
            cin.clear();
            cin.ignore(1000,'\n');  //防止cin一直为错误状态
            
            continue;
        }
        else
        {
            cout << "你选择了" << selection <<endl;
            gotomenu(selection);    //跳转菜单
            break;
        }
    }
    cout << "Hello World!\n";
    exitprogram();
}

void initprogram() {	//初始化程序
    //添加读取文件，配置等函数
}

void printmenu() {	//打印菜单
    cout << "|================== 家庭财务管理系统 ==================|\n"
        << "|Version: 1.0.0                                        |\n"
        << "|                                                      |\n"
        << "|Authors: hidacow,Davidguess,Ch-franck,medicalpants    |\n"
        << "|                                                      |\n"
        << "|--菜单------------------------------------------------|\n"
        << "|----收入管理------------------------------------------|\n"
        << "|      1. 添加收入                                     |\n"
        << "|      2. 编辑收入                                     |\n"
        << "|      3. 删除收入                                     |\n"
        << "|      4. 查询收入                                     |\n"
        << "|----支出管理------------------------------------------|\n"
        << "|      5. 添加支出                                     |\n"
        << "|      6. 编辑支出                                     |\n"
        << "|      7. 删除支出                                     |\n"
        << "|      8. 查询支出                                     |\n"
        << "|----统计----------------------------------------------|\n"
        << "|      9. 收入排序                                     |\n"
        << "|     10. 支出排序                                     |\n"
        << "|     11. 导出报表                                     |\n"
        << "|----其它----------------------------------------------|\n"
        << "|     12. 设置/修改操作密码                            |\n"
        << "|     13. 退出程序                                     |\n"
        << "|======================================================|\n";
}

void gotomenu(int menuno) {	//跳转菜单
    switch (menuno)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;

    case 13:
        exitprogram();
        break;
    default:
        break;
    }
}

void exitprogram() {	//退出程序
    //添加确认退出提示、文件保存等函数
    exit(0);	//退出并返回0
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
