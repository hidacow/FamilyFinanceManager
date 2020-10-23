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
    
    if (isinit) {
        initprogram();  
        isinit = true;
    }
    selectmenu();
    
    return 0;
}

void initprogram() {	
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

void printtitle(string title) {
    cout << "=================== 家庭财务管理系统 ===================\n"
        << "----[" << title << "]----" << endl;
}

void selectmenu() {
    int selection;
    while (true)
    {
        system("cls");  //清屏
        printmenu();    //打印主菜单
        cout << "请选择菜单 [1-" << MAIN_MENU_COUNT << "]:";
        selection = 0;
        cin >> selection;
        if (cin.fail() || selection<1 || selection > MAIN_MENU_COUNT)
        {
            cout << "输入错误！" << endl;
            system("pause");    //让用户按任意键继续
            cin.clear();
            cin.ignore(1000, '\n');
              //防止cin一直为错误状态

            continue;
        }
        else
        {
            gotomenu(selection);    //跳转菜单
            break;
        }
    }
}

void gotomenu(int menuno) {	
    switch (menuno)
    {
    case 1:
        addincome();
        break;
    case 2:
        editincome();
        break;
    case 3:
        delincome();
        break;
    case 4:
        queryincome();
        break;
    case 5:
        addexpense();
        break;
    case 6:
        editexpense();
        break;
    case 7:
        delexpense();
        break;
    case 8:
        queryexpense();
        break;
    case 9:
        sortincome();
        break;
    case 10:
        sortexpense();
        break;
    case 11:
        delexpense();
        break;
    case 12:
        editpassword();
        break;
    case 13:
        exitprogram();
        break;
    default:
        break;
    }
}

void exitprogram() {
    
    string confirmation;
    cout << "你真的要退出吗？(输入y以退出)";
    cin >> confirmation;
    if (confirmation == "y"|| confirmation == "Y") {
        //添加文件保存等函数
        exit(0);//退出并返回0
    }
    else {
        cin.clear();
        selectmenu();
    }
}

void clearFianceItem(FinanceItem& item) {
    item.detail = "";
    item.money = 0;
    item.month = 0;
    item.year = 0;
    item.name = "";
}

void addincome() {
    FinanceItem fiinfo;
    string confirmation = "";
    do
    {
        clearFianceItem(fiinfo);    //Initialize it
        fiinfo.type = 1;    //此处是收入
        system("cls");  //清屏
        printtitle("添加收入");
        inputinfo(fiinfo);
        cout << endl << "请确认:" << endl << "----------------" << endl;
        cout << "姓名:" << fiinfo.name << endl
            << "时间:" << fiinfo.year << "/" << fiinfo.month << endl
            << "支出:" << fixed << setprecision(2) << fiinfo.money << "元" << endl
            << "备注:" << fiinfo.detail << endl << "----------------" << endl;
        cout << "确定添加？(输入y继续,输入c取消,输入其它重输)";
        cin >> confirmation;
        if (confirmation == "c") {
            selectmenu();
            return;
        }
    } while (confirmation != "y" && confirmation != "Y");
    
    cout << "添加成功！" << endl;
    system("pause");
    selectmenu();
    //添加保存到文件


}

void inputinfo(FinanceItem& financeinfo) {
    cout << "请输入家庭成员姓名:";
    while (1) {
        while (getline(cin, financeinfo.name))
        {
            if (financeinfo.name != "") {
                cin.clear(); break;
            }
        }
        if (cin.good()) break;
        else {
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
    cout << endl << "请输入年份(yyyy):";
    while (1) {
        cin >> financeinfo.year;
        if (cin.good()&& financeinfo.year > 1800) break;
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "输入错误!请重新输入:";
        }
    }
    cin.clear();
    cin.ignore(1000, '\n');
    cout<<endl<< "请输入月份(m):";
    while (1) {
        cin >> financeinfo.month;
        if (cin.good()&& financeinfo.month <= 12 && financeinfo.month >= 1) break;
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "输入错误!请重新输入:";
        }
    }
    cin.clear();
    cin.ignore(1000, '\n');
    cout << endl << "请输入金额:";
    while (1) {
        cin >> financeinfo.money;
        if (cin.good()&& financeinfo.money > 0) break;
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "输入错误!请重新输入:";
        }
    }
    cin.clear();
    cin.ignore(1000, '\n');
    cout << endl << "请输入备注:";
    while (getline(cin,financeinfo.detail))
    {
        if (financeinfo.detail != "") {
            cin.clear(); break;
        }
    }
}

void editincome() {

}
void delincome() {

}

void addexpense() {

}
void editexpense() {
    
}
void delexpense() {

}

void sortincome() {

}

void sortexpense() {

}

void queryincome() {

}

void queryexpense() {

}

void exporttable() {

}

void editpassword() {

}

bool validatepassword(string pwd) {
    return true;
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
