// FamilyFinance.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//养成写注释和缩进的好习惯，让自己也让别人看得懂
//注释：在一行后按一次tab打//开始写注释
/*
或者也可以这样写
多行注释
*/

#include "FamilyFinance.h"  //调用头文件


int main()
{
    
    if (!isinit) {  //如果程序尚未初始化
        initprogram();  //初始化程序
        isinit = true;  //标记已初始化
    }
    selectmenu();   //选择菜单
    
    return 0;
}

void initprogram() {	
    getfromfile();
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
        savetofile();
        exit(0);//退出并返回0
    }
    else {
        cin.clear();
        selectmenu();
    }
}

void clearFinanceItem(FinanceItem& item) {
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
        clearFinanceItem(fiinfo);    //Initialize it
        fiinfo.type = 1;    //此处是收入
        system("cls");  //清屏
        printtitle("添加收入");
        inputinfo(fiinfo);
        cout << endl << "请确认:" << endl << "----------------" << endl;
        cout << "姓名:" << fiinfo.name << endl
            << "时间:" << fiinfo.year << "/" << fiinfo.month << endl
            << "收入:" << fixed << setprecision(2) << fiinfo.money << "元" << endl
            << "备注:" << fiinfo.detail << endl << "----------------" << endl;
        cout << "确定添加？(输入y继续,输入c取消,输入其它重输)";
        cin >> confirmation;
        if (confirmation == "c") {
            selectmenu();
            return;
        }
    } while (confirmation != "y" && confirmation != "Y");
    FinanceBook.push_back(fiinfo);
    savetofile();
    cout << "添加成功！" << endl;
    system("pause");
    selectmenu();
}

void inputinfo(FinanceItem& financeinfo) {
    cout << "请输入家庭成员姓名:";
    while (1) {
        getline(cin, financeinfo.name);

        if (isNameLegal(financeinfo.name)) {
            cin.clear();
            break;
        }
        else if (financeinfo.name != "") {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "姓名不合法!请重新输入:";
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
        //if (financeinfo.detail != "") {
            cin.clear(); break;
        //}
    }
}

unsigned char ToHex(unsigned char x)
{
    return  x > 9 ? x + 55 : x + 48;
}

unsigned char FromHex(unsigned char x)
{
    unsigned char y;
    if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
    else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
    else if (x >= '0' && x <= '9') y = x - '0';
    else assert(0);
    return y;
}

string UrlEncode(const string& str) //对字符串进行URL编码
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)str[i]) ||
            (str[i] == '-') ||
            (str[i] == '_') ||
            (str[i] == '.') ||
            (str[i] == '~'))
            strTemp += str[i];
        else if (str[i] == ' ')
            strTemp += "+";
        else
        {
            strTemp += '%';
            strTemp += ToHex((unsigned char)str[i] >> 4);
            strTemp += ToHex((unsigned char)str[i] % 16);
        }
    }
    return strTemp;
}

string UrlDecode(const string& str) //对字符串进行URL解码
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (str[i] == '+') strTemp += ' ';
        else if (str[i] == '%')
        {
            assert(i + 2 < length);
            unsigned char high = FromHex((unsigned char)str[++i]);
            unsigned char low = FromHex((unsigned char)str[++i]);
            strTemp += high * 16 + low;
        }
        else strTemp += str[i];
    }
    return strTemp;
}

void savetofile() {
    cout << "写入数据文件..." << endl;
    ofstream output(DATA_FILE,ios_base::binary);
    if (FinanceBook.size() == 0) { cout << "无数据..." << endl; output.close(); return; }
    output << FinanceBook.size();
    for (int i = 0; i < FinanceBook.size(); i++) {
        output <<" "<< FinanceBook[i].type <<" " << UrlEncode(FinanceBook[i].name) << " " << FinanceBook[i].year << " " << FinanceBook[i].month << " " << FinanceBook[i].money << " " << UrlEncode(FinanceBook[i].detail);
    }
    cout << "写入了" << FinanceBook.size() << "条数据" << endl;
    output.close();
    cout << "写入完成" << endl;
}

void getfromfile() {
    cout << "加载数据文件..." << endl;
    ifstream input(DATA_FILE, ios_base::binary);
    FinanceBook.clear();
    int cnt=0;
    input >> cnt;
    if (cnt == 0) { cout << "无数据文件或文件损坏！" << endl; input.close(); return; }
    FinanceItem a;
    for (int i = 0; i < cnt; i++) {
        input >> a.type >> a.name >> a.year >> a.month >> a.money >> a.detail;
        a.name = UrlDecode(a.name);
        a.detail = UrlDecode(a.detail);
        FinanceBook.push_back(a);
    }
    cout << "加载了"<<FinanceBook.size()<<"条数据" << endl;
    input.close();
    cout << "加载完成" << endl;
}

bool cmp(FinanceItem a, FinanceItem b) {
    
    if (a.type == b.type) { //先判断收支类型
        if (!issortnamefirst)   //判断是否姓名优先排序
        {
            if (a.year == b.year) { //判断年份
               if (a.month == b.month) { //判断月份
                    if (a.name == b.name) { //判断姓名
                        if (a.money == b.money) {
                            return a.detail < b.detail; //按备注的字母序排序
                        }else return a.money > b.money; //金额大的在前
                    }else return a.name < b.name;   //按名字字母序排序
                }else if (issortrecent)return a.month > b.month;    //最近的月份在前
                else return a.month < b.month;
            }else if(issortrecent)return a.year > b.year;   //最近的年份在前
            else return a.year < b.year;
        }
        else {
            if (a.name == b.name) {
                if (a.year == b.year) {
                    if (a.month == b.month) {
                        if (a.money == b.money) {
                            return a.detail < b.detail;
                        }
                        else return a.money > b.money;
                    }
                    else if (issortrecent)return a.month > b.month;
                    else return a.month < b.month;
                }
                else if (issortrecent)return a.year > b.year;
                else return a.year < b.year;
            }else return a.name < b.name;
        }
        
    }
    else if (issortincome) return a.type > b.type;  //收入在前
    else return a.type < b.type;    //支出在后
    
}

void editincome() {

}
void delincome() {

}

void addexpense() {
    FinanceItem fiinfo;
    string confirmation = "";
    do
    {
        clearFinanceItem(fiinfo);    //Initialize it
        fiinfo.type = -1;    //此处是支出
        system("cls");  //清屏
        printtitle("添加支出");
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
    FinanceBook.push_back(fiinfo);
    savetofile();
    cout << "添加成功！" << endl;
    system("pause");
    selectmenu();
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
    FinanceItem targetinfo;
    string confirmation = "";
    
    clearFinanceItem(targetinfo);    //Initialize it
    targetinfo.type = 1;    //此处是收入
    system("cls");  //清屏
    printtitle("查询收入");
    inputquerycondition(targetinfo);

    bool flag = false;
    double sumincome = 0;
    vector<FinanceItem>queryresult;

    issortincome = true;issortrecent = true;issortnamefirst = false;    //排序参数
    sort(FinanceBook.begin(), FinanceBook.end(), cmp);  //结构体排序
    
    for (int i = 0; i < FinanceBook.size(); ++i) {
        if (FinanceBook[i].type != targetinfo.type)break;
        if (targetinfo.year ==-1 || FinanceBook[i].year == targetinfo.year) {
            if (targetinfo.month == -1 || FinanceBook[i].month == targetinfo.month) {
                if (targetinfo.name =="*"||FinanceBook[i].name == targetinfo.name) {
                    queryresult.push_back(FinanceBook[i]);
                    sumincome += FinanceBook[i].money;
                    flag = true;
                }
            }
            else if ((targetinfo.year != -1 && targetinfo.month != -1)&&flag)break;    //精确查询状态程序优化
        }else if ((targetinfo.year != -1 && targetinfo.month != -1) && flag)break;   //精确查询状态程序优化
    }
    cout<<endl<< "----[查询结果]----" ;
    if (queryresult.size() == 0) {
        cout << endl <<endl<< "无结果" << endl << endl;
    }
    else {
        issortnamefirst = true;
        sort(queryresult.begin(), queryresult.end(), cmp);
        
        string currentname = ""; int currentyear = 0; int currentmonth = 0;
        for (int i = 0; i < queryresult.size(); i++)
        {
            if (currentname != queryresult[i].name) {
                cout <<endl << endl << "姓名:" << queryresult[i].name << endl;
                currentname = queryresult[i].name;
                currentyear = 0; currentmonth = 0;
            }
            if (currentyear != queryresult[i].year || currentmonth != queryresult[i].month) {
                currentyear= queryresult[i].year;
                currentmonth = queryresult[i].month;
                cout <<endl<< "时间:" << queryresult[i].year << "/" << queryresult[i].month <<endl
                    << "------------------" << endl;
            }
            cout << "收入:" << fixed << setprecision(2) << queryresult[i].money << "元" << endl
                << "备注:" << queryresult[i].detail << endl << "------------------" << endl;
        }
        
        
        
    }
    if(sumincome!=0)cout << endl << "共计:" << sumincome << "元" << endl;
    if (queryresult.size() != 0)cout << queryresult.size() << "条记录" << endl;
    cout<< "------------------" << endl;
    system("pause");
    selectmenu();
}

void inputquerycondition(FinanceItem& financeinfo) {
    cout << "请输入家庭成员姓名(输入*代表查询全部):";
    while (1) {
        getline(cin, financeinfo.name);
        
        if (isNameLegal(financeinfo.name,true)) {
                cin.clear();
                break;
        }
        else if(financeinfo.name!=""){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "姓名不合法!请重新输入:";
        }
        
    }
    cout << endl << "请输入年份(输入-1代表查询全部):";
    while (1) {
        cin >> financeinfo.year;
        if (cin.good() && (financeinfo.year > 1800||financeinfo.year==-1)) break;
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "输入错误!请重新输入:";
        }
    }
    cin.clear();
    cin.ignore(1000, '\n');
    cout << endl << "请输入月份(输入-1代表查询全部):";
    while (1) {
        cin >> financeinfo.month;
        if (cin.good() && (financeinfo.month <= 12 && financeinfo.month >= 1||financeinfo.month==-1)) break;
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "输入错误!请重新输入:";
        }
    }
    cin.clear();
    cin.ignore(1000, '\n');
}

bool isNameLegal(string name,bool isallowstarmark) {
    if (name == "")return false;
    string tmpstr=string(name.size(),' ');
    if (tmpstr == name)return false;    //不能全为空格
    if (name == "*"&&(!isallowstarmark))return false;   //不能为*
    return true;
}

void queryexpense() {
    FinanceItem targetinfo;
    string confirmation = "";

    clearFinanceItem(targetinfo);    //Initialize it
    targetinfo.type = -1;    //此处是支出
    system("cls");  //清屏
    printtitle("查询支出");
    inputquerycondition(targetinfo);

    bool flag = false;
    double sumincome = 0;
    vector<FinanceItem>queryresult;

    issortincome = false; issortrecent = true; issortnamefirst = false;    //排序参数
    sort(FinanceBook.begin(), FinanceBook.end(), cmp);  //结构体排序

    for (int i = 0; i < FinanceBook.size(); ++i) {
        if (FinanceBook[i].type != targetinfo.type)break;
        if (targetinfo.year == -1 || FinanceBook[i].year == targetinfo.year) {
            if (targetinfo.month == -1 || FinanceBook[i].month == targetinfo.month) {
                if (targetinfo.name == "*" || FinanceBook[i].name == targetinfo.name) {
                    queryresult.push_back(FinanceBook[i]);
                    sumincome += FinanceBook[i].money;
                    flag = true;
                }
            }
            else if ((targetinfo.year != -1 && targetinfo.month != -1) && flag)break;    //精确查询状态程序优化
        }
        else if ((targetinfo.year != -1 && targetinfo.month != -1) && flag)break;   //精确查询状态程序优化
    }
    cout << endl << "----[查询结果]----";
    if (queryresult.size() == 0) {
        cout << endl << endl << "无结果" << endl << endl;
    }
    else {
        issortnamefirst = true;
        sort(queryresult.begin(), queryresult.end(), cmp);

        string currentname = ""; int currentyear = 0; int currentmonth = 0;
        for (int i = 0; i < queryresult.size(); i++)
        {
            if (currentname != queryresult[i].name) {
                cout << endl << endl << "姓名:" << queryresult[i].name << endl;
                currentname = queryresult[i].name;
                currentyear = 0; currentmonth = 0;
            }
            if (currentyear != queryresult[i].year || currentmonth != queryresult[i].month) {
                currentyear = queryresult[i].year;
                currentmonth = queryresult[i].month;
                cout << endl << "时间:" << queryresult[i].year << "/" << queryresult[i].month << endl
                    << "------------------" << endl;
            }
            cout << "支出:" << fixed << setprecision(2) << queryresult[i].money << "元" << endl
                << "备注:" << queryresult[i].detail << endl << "------------------" << endl;
        }



    }
    if (sumincome != 0)cout << endl << "共计:" << sumincome << "元" << endl;
    if (queryresult.size() != 0)cout << queryresult.size() << "条记录" << endl;
    cout << "------------------" << endl;
    system("pause");
    selectmenu();

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
