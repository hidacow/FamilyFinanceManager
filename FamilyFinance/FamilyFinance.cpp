#define _CRT_SECURE_NO_WARNINGS
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
    time_t now = time(0);  //声明time_t类型变量
    struct tm* t = localtime(&now);//获取系统日期和时间
    sysyear = 1900 + t->tm_year;
    sysmonth = 1 + t->tm_mon;
    //struct tm t;   //tm结构指针
    //time_t now;  //声明time_t类型变量
    //time(&now);      //获取系统日期和时间
    //localtime_s(&t, &now);
    //sysyear = 1900+t.tm_year;
    //sysmonth = 1+t.tm_mon;
    getfromfile();
}

void printmenu() {	//打印菜单
    cout << "|================== 家庭财务管理系统 ==================|\n"
        << "|Version: 1.0.0                                        |\n"
        << "|                                                      |\n"
        << "|Authors: hidacow,Davidguess,medicalpants,Ch-franck    |\n"
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
        << "|      9. 导出报表                                     |\n"
        << "|----排序设置------------------------------------------|\n"
        << "|     10. 时间                                         |\n"
        << "|     11. 数额                                         |\n"
        << "|----其它----------------------------------------------|\n"
        << "|     12. 关于程序                                     |\n"
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
            cout << "输入错误!" << endl;
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
    string c;
    
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
        exporttable();
        break;
    case 10:
        setsortrecent();
        break;
    case 11:
        setsortbiggeramount();
        break;
    case 12:
        showabout();
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
    cout << "你真的要退出吗?(输入y以退出)";
    cin >> confirmation;
    if (confirmation == "y"|| confirmation == "Y") {
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
        fiinfo.year = sysyear;    //初始赋值系统年份
        fiinfo.month = sysmonth;    //初始赋值系统月份
        system("cls");  //清屏
        printtitle("添加收入");
        inputinfo(fiinfo);
        cout << endl << "请确认:" << endl << "----------------" << endl;
        cout << "姓名:" << fiinfo.name << endl
            << "时间:" << fiinfo.year << "/" << fiinfo.month << endl
            << "收入:" << fixed << setprecision(2) << fiinfo.money << "元" << endl
            << "备注:" << fiinfo.detail << endl << "----------------" << endl;
        cout << "确定添加?(输入y继续,输入c取消,输入其它重输)";
        cin >> confirmation;    
        if (confirmation == "c") {
            selectmenu();
            return;
        }
    } while (confirmation != "y" && confirmation != "Y");   //用户确认
    FinanceBook.push_back(fiinfo);
    savetofile();   //写入到文件
    cout << "添加成功!" << endl;
    system("pause");    //输入任意数继续
    selectmenu();   //选择菜单
}

void inputinfo(FinanceItem& financeinfo) {
    string tmp="";  //姓名字符串
    if (financeinfo.name != "")tmp = "(默认:"+financeinfo.name+")";   //不输入时默认姓名
    cout << "请输入姓名"<<tmp<<":";    
    getline(cin, tmp);
    while (1) {
        auto oval = financeinfo.name;
        getline(cin, financeinfo.name);
        if (financeinfo.name == "")financeinfo.name = oval;
        if (isNameLegal(financeinfo.name)) {
            cin.clear();
            break;
        }
        else if (financeinfo.name != "") {
            /*cin.clear();
            cin.ignore(1000, '\n');*/
            cout << "姓名不合法!请重新输入:";
        }

    }   //重复输入姓名直到姓名合法
    tmp = "";   //月份字符串
    if (financeinfo.year != 0)tmp = "(默认:" + to_string(financeinfo.year) + ")";     //不输入时默认年份
    cout << endl << "请输入年份"<<tmp<<":";
    while (1) {
        auto oval = financeinfo.year;
        getline(cin, tmp);
        if (tmp == "") {
            financeinfo.year = oval;
        }
        else
        {
            istringstream istr(tmp);
            istr >> financeinfo.year;
        }
        if (financeinfo.year > 1800) break;
        else {
            /*cin.clear();
            cin.ignore(1000, '\n');*/
            cout << "输入错误!请重新输入:";
        }
    }   //重复输入年份直到年份正确（<=当前年份）
    tmp = "";   //月份字符串
    if (financeinfo.month != 0)tmp = "(默认:" + to_string(financeinfo.month) + ")";   //不输入时默认月份
    cout << endl << "请输入月份" << tmp << ":";
    while (1) {
        auto oval = financeinfo.month;
        getline(cin, tmp);
        if (tmp == "") {
            financeinfo.month = oval;
        }
        else
        {
            istringstream istr(tmp);
            istr >> financeinfo.month;
        }
        if (financeinfo.month > 0&&financeinfo.month<13) break;
        else {
            /*cin.clear();
            cin.ignore(1000, '\n');*/
            cout << "输入错误!请重新输入:";
        }
    }   //重复输入直到月份正确
    tmp = "";   //金额字符串
    if (financeinfo.money != 0)cout << endl << "请输入金额(默认:" << fixed<<setprecision(2)<< financeinfo.money << "):"; //不输入时默认金额
    else cout << endl << "请输入金额:";
    while (1) {
        auto oval = financeinfo.money;
        getline(cin, tmp);
        if (tmp == "") {
            if (oval != 0)financeinfo.money = oval;
            else financeinfo.money = -1;
        }
        else
        {
            istringstream istr(tmp);
            istr >> financeinfo.money;
        }
        if (financeinfo.money > 0) break;
        else {
            /*cin.clear();
            cin.ignore(1000, '\n');*/
            cout << "输入错误!请重新输入:";
        }
    }   //重复输入直到金额正确
    tmp = "";   //备注字符串
    if (financeinfo.detail != "")tmp = "(默认:" + financeinfo.detail + ")";
    cout <<endl<< "请输入备注" << tmp << ":";
    //getline(cin, tmp);
    while (1) {
        auto oval = financeinfo.detail;
        getline(cin, financeinfo.detail);
        
        if (financeinfo.detail == "" && oval != "")financeinfo.detail = oval;
        else if(financeinfo.detail=="")financeinfo.detail = " ";
        break;

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
    if (output.fail()) {
        cout << "打开文件失败！" << endl;
        return;
    }
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
    if (input.fail()) {
        cout << "打开文件失败！" << endl;
        return;
    }
    FinanceBook.clear();
    int cnt=0;
    input >> cnt;
    if (cnt == 0) { cout << "无数据文件或文件损坏!" << endl; input.close(); return; }
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
                        }else if(issortbiggeramount)return a.money > b.money; //金额大的在前
                        else return a.money < b.money;
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
                        else if (issortbiggeramount)return a.money > b.money;
                        else return a.money < b.money;
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
    FinanceItem targetinfo;
    string confirmation = "";

    clearFinanceItem(targetinfo);    //Initialize it
    targetinfo.type = 1;    //此处是收入
    system("cls");  //清屏
    printtitle("编辑收入");
    inputquerycondition(targetinfo);

    bool flag = false;
    double sumincome = 0;
    vector<FinanceItem>queryresult;

    issortincome = true; issortnamefirst = false;  //排序参数
    sort(FinanceBook.begin(), FinanceBook.end(), cmp);  //结构体排序
    //以下为筛选
    for (int i = 0; i < FinanceBook.size(); ++i) {
        if (FinanceBook[i].type != targetinfo.type)break;
        if (targetinfo.year == -1 || FinanceBook[i].year == targetinfo.year) {
            if (targetinfo.month == -1 || FinanceBook[i].month == targetinfo.month) {
                if (targetinfo.name == "*" || FinanceBook[i].name == targetinfo.name) {
                    queryresult.push_back(FinanceBook[i]);
                    sumincome += FinanceBook[i].money;
                    FinanceBook.erase(FinanceBook.begin() + i);
                    i--;
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
            cout << "No." << i + 1 << endl;
            cout << "收入:" << fixed << setprecision(2) << queryresult[i].money << "元" << endl
                << "备注:" << queryresult[i].detail << endl << "------------------" << endl;
        }



    }
    
    cout << "------------------" << endl;
    int selection;
    if (queryresult.size() == 0)
    {
        cout << "没有找到可供编辑的记录" << endl;
        
    }
    else {
        while (true)
        {

            cout << "请选择编号 [1-" << queryresult.size() << "]，输入-1取消:";
            selection = 0;
            cin >> selection;
            if (selection == -1) {
                for (int i = 0; i < queryresult.size(); i++) {
                    FinanceBook.push_back(queryresult[i]);
                }
                cout << "取消了操作"<<endl;
                break;
            }
            if (cin.fail() || selection<1 || selection > queryresult.size())
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
                FinanceItem fiinfo;
                string confirmation = "";
                do
                {
                    fiinfo = queryresult[selection - 1];

                    inputinfo(fiinfo);
                    cout << endl << "请确认:" << endl << "----------------" << endl;
                    cout << "姓名:" << fiinfo.name << endl
                        << "时间:" << fiinfo.year << "/" << fiinfo.month << endl
                        << "收入:" << fixed << setprecision(2) << fiinfo.money << "元" << endl
                        << "备注:" << fiinfo.detail << endl << "----------------" << endl;
                    cout << "确定修改?(输入y继续,输入c取消,输入其它重输)";
                    cin >> confirmation;
                    if (confirmation == "c") {
                        for (int i = 0; i < queryresult.size(); i++) {
                            FinanceBook.push_back(queryresult[i]);
                        }
                        cout << "取消了操作" << endl;
                        break;
                    }
                } while (confirmation != "y" && confirmation != "Y");
                queryresult[selection - 1] = fiinfo;
                
                for (int i = 0; i < queryresult.size(); i++) {
                    FinanceBook.push_back(queryresult[i]);

                }
                savetofile();
                cout << "修改成功" << endl;
                break;
            }

        }
    }
    system("pause");
    selectmenu();
}
void delincome() {
    FinanceItem targetinfo;
    string confirmation = "";

    clearFinanceItem(targetinfo);    //Initialize it
    targetinfo.type = 1;    //此处是收入
    system("cls");  //清屏
    printtitle("删除收入");
    inputquerycondition(targetinfo);

    bool flag = false;
    double sumincome = 0;
    vector<FinanceItem>queryresult;

    issortincome = true;  issortnamefirst = false;   //排序参数
    sort(FinanceBook.begin(), FinanceBook.end(), cmp);  //结构体排序
    //以下是筛选
    for (int i = 0; i < FinanceBook.size(); ++i) {
        if (FinanceBook[i].type != targetinfo.type)break;
        if (targetinfo.year == -1 || FinanceBook[i].year == targetinfo.year) {
            if (targetinfo.month == -1 || FinanceBook[i].month == targetinfo.month) {
                if (targetinfo.name == "*" || FinanceBook[i].name == targetinfo.name) {
                    queryresult.push_back(FinanceBook[i]);
                    sumincome += FinanceBook[i].money;
                    FinanceBook.erase(FinanceBook.begin() + i);
                    i--;
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
            cout << "No." << i + 1 << endl;
            cout << "收入:" << fixed << setprecision(2) << queryresult[i].money << "元" << endl
                << "备注:" << queryresult[i].detail << endl << "------------------" << endl;
        }



    }
    /*if (sumincome != 0)cout << endl << "共计:" << sumincome << "元" << endl;
    if (queryresult.size() != 0)cout << queryresult.size() << "条记录" << endl;*/
    cout << "------------------" << endl;
    int selection;
    if (queryresult.size()==0)
    {
        cout << "没有找到可供删除的记录" << endl;

    }
    else {
        while (true)
        {

            cout << "请选择编号 [1-" << queryresult.size() << "]，输入-1取消:";
            selection = 0;
            cin >> selection;
            if (selection == -1) {
                for (int i = 0; i < queryresult.size(); i++) {
                    FinanceBook.push_back(queryresult[i]);
                }
                cout << "取消了操作" << endl;
                break;
            }
            if (cin.fail() || selection<1 || selection > queryresult.size())
            {
                cout << "输入错误!" << endl;
                system("pause");    //让用户按任意键继续
                cin.clear();
                cin.ignore(1000, '\n');
                //防止cin一直为错误状态

                continue;
            }
            else
            {
                queryresult.erase(queryresult.begin() + selection - 1);
                for (int i = 0; i < queryresult.size(); i++) {
                    FinanceBook.push_back(queryresult[i]);

                }
                savetofile();
                cout << "删除成功" << endl;
                break;
            }

        }
    }
    system("pause");
    selectmenu();
}

void addexpense() {
    FinanceItem fiinfo;
    string confirmation = "";
    do
    {
        clearFinanceItem(fiinfo);    //Initialize it
        fiinfo.type = -1;    //此处是支出
        fiinfo.year = sysyear;
        fiinfo.month = sysmonth;
        system("cls");  //清屏
        printtitle("添加支出");
        inputinfo(fiinfo);
        cout << endl << "请确认:" << endl << "----------------" << endl;
        cout << "姓名:" << fiinfo.name << endl
            << "时间:" << fiinfo.year << "/" << fiinfo.month << endl
            << "支出:" << fixed << setprecision(2) << fiinfo.money << "元" << endl
            << "备注:" << fiinfo.detail << endl << "----------------" << endl;
        cout << "确定添加?(输入y继续,输入c取消,输入其它重输)";
        //以下为用户确认
        cin >> confirmation;
        if (confirmation == "c") {
            selectmenu();
            return;
        }
    } while (confirmation != "y" && confirmation != "Y");
    FinanceBook.push_back(fiinfo);
    savetofile();
    cout << "添加成功!" << endl;
    system("pause");    //按任意键回到主菜单
    selectmenu();   
}
void editexpense() {
    FinanceItem targetinfo;
    string confirmation = "";

    clearFinanceItem(targetinfo);    //Initialize it
    targetinfo.type = -1;    //此处是支出
    system("cls");  //清屏
    printtitle("编辑支出");
    inputquerycondition(targetinfo);

    bool flag = false;
    double sumincome = 0;
    vector<FinanceItem>queryresult;

    issortincome = false;  issortnamefirst = false;    //排序参数
    sort(FinanceBook.begin(), FinanceBook.end(), cmp);  //结构体排序
    //以下为筛选
    for (int i = 0; i < FinanceBook.size(); ++i) {
        if (FinanceBook[i].type != targetinfo.type)break;
        if (targetinfo.year == -1 || FinanceBook[i].year == targetinfo.year) {
            if (targetinfo.month == -1 || FinanceBook[i].month == targetinfo.month) {
                if (targetinfo.name == "*" || FinanceBook[i].name == targetinfo.name) {
                    queryresult.push_back(FinanceBook[i]);
                    sumincome += FinanceBook[i].money;
                    FinanceBook.erase(FinanceBook.begin() + i);
                    i--;
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
            cout << "No." << i + 1 << endl;
            cout << "支出:" << fixed << setprecision(2) << queryresult[i].money << "元" << endl
                << "备注:" << queryresult[i].detail << endl << "------------------" << endl;
        }



    }
    /*if (sumincome != 0)cout << endl << "共计:" << sumincome << "元" << endl;
    if (queryresult.size() != 0)cout << queryresult.size() << "条记录" << endl;*/
    cout << "------------------" << endl;
    int selection;
    if (queryresult.size() == 0)
    {
        cout << "没有找到可供编辑的记录" << endl;

    }
    else {
        while (true)
        {

            cout << "请选择编号 [1-" << queryresult.size() << "]，输入-1取消:";
            selection = 0;
            cin >> selection;
            if (selection == -1) {
                for (int i = 0; i < queryresult.size(); i++) {
                    FinanceBook.push_back(queryresult[i]);
                }
                cout << "取消了操作"<<endl;
                break;
            }
            if (cin.fail() || selection<1 || selection > queryresult.size())
            {
                cout << "输入错误!" << endl;
                system("pause");    //让用户按任意键继续
                cin.clear();
                cin.ignore(1000, '\n');
                //防止cin一直为错误状态

                continue;
            }
            else
            {
                FinanceItem fiinfo;
                string confirmation = "";
                do
                {
                    fiinfo = queryresult[selection - 1];

                    inputinfo(fiinfo);
                    cout << endl << "请确认:" << endl << "----------------" << endl;
                    cout << "姓名:" << fiinfo.name << endl
                        << "时间:" << fiinfo.year << "/" << fiinfo.month << endl
                        << "收入:" << fixed << setprecision(2) << fiinfo.money << "元" << endl
                        << "备注:" << fiinfo.detail << endl << "----------------" << endl;
                    cout << "确定修改?(输入y继续,输入c取消,输入其它重输)";
                    cin >> confirmation;
                    if (confirmation == "c") {
                        for (int i = 0; i < queryresult.size(); i++) {
                            FinanceBook.push_back(queryresult[i]);
                        }
                        cout << "取消了操作" << endl;
                        break;
                    }
                } while (confirmation != "y" && confirmation != "Y");
                queryresult[selection - 1] = fiinfo;

                for (int i = 0; i < queryresult.size(); i++) {
                    FinanceBook.push_back(queryresult[i]);
                }
                savetofile();
                cout << "修改成功" << endl;
                break;
            }

        }
    }
    system("pause");
    selectmenu();
}
void delexpense() {
    FinanceItem targetinfo;
    string confirmation = "";

    clearFinanceItem(targetinfo);    //Initialize it
    targetinfo.type = -1;    //此处是支出
    system("cls");  //清屏
    printtitle("删除支出");
    inputquerycondition(targetinfo);

    bool flag = false;
    double sumincome = 0;
    vector<FinanceItem>queryresult;

    issortincome = false;  issortnamefirst = false; //排序参数
    sort(FinanceBook.begin(), FinanceBook.end(), cmp);  //结构体排序

    for (int i = 0; i < FinanceBook.size(); ++i) {
        if (FinanceBook[i].type != targetinfo.type)break;
        if (targetinfo.year == -1 || FinanceBook[i].year == targetinfo.year) {
            if (targetinfo.month == -1 || FinanceBook[i].month == targetinfo.month) {
                if (targetinfo.name == "*" || FinanceBook[i].name == targetinfo.name) {
                    queryresult.push_back(FinanceBook[i]);
                    sumincome += FinanceBook[i].money;
                    FinanceBook.erase(FinanceBook.begin() + i);
                    i--;
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
            cout << "No." << i + 1 << endl;
            cout << "支出:" << fixed << setprecision(2) << queryresult[i].money << "元" << endl
                << "备注:" << queryresult[i].detail << endl << "------------------" << endl;
        }



    }
    /*if (sumincome != 0)cout << endl << "共计:" << sumincome << "元" << endl;
    if (queryresult.size() != 0)cout << queryresult.size() << "条记录" << endl;*/
    cout << "------------------" << endl;
    int selection;
    if (queryresult.size() == 0)
    {
        cout << "没有找到可供删除的记录" << endl;

    }
    else {
        while (true)
        {

            cout << "请选择编号 [1-" << queryresult.size() << "]，输入-1取消:";
            selection = 0;
            cin >> selection;
            if (selection == -1) {
                for (int i = 0; i < queryresult.size(); i++) {
                    FinanceBook.push_back(queryresult[i]);
                }
                cout << "取消了操作" << endl;
                break;
            }
            if (cin.fail() || selection<1 || selection > queryresult.size())
            {
                cout << "输入错误!" << endl;
                system("pause");    //让用户按任意键继续
                cin.clear();
                cin.ignore(1000, '\n');
                //防止cin一直为错误状态

                continue;
            }
            else
            {
                queryresult.erase(queryresult.begin() + selection - 1);
                for (int i = 0; i < queryresult.size(); i++) {
                    FinanceBook.push_back(queryresult[i]);

                }
                savetofile();
                cout << "删除成功" << endl;
                break;
            }

        }
    }
    system("pause");
    selectmenu();
}

void setsortrecent() {
    system("cls");  //清屏
    printtitle("排序设置");
    cout << "设置查询结果中优先展示最近月份的收支" << endl;
    cout << "当前：";
    if (issortrecent)cout << "是" << endl;
    else cout << "否" << endl;
    cout << "输入y更改为\"是\",输入n更改为\"否\",输入其它取消: ";
    string selection;
    cin >> selection;
    if (selection == "y" || selection == "Y")issortrecent = true;
    else if (selection == "n" || selection == "N")issortrecent = false;
    else {
        cout << "取消了操作" << endl;
        system("pause");
        selectmenu();
        return;
    }
    cout << "修改设置成功" << endl;
    system("pause");
    selectmenu();
    return;
}

void setsortbiggeramount() {
    system("cls");  //清屏
    printtitle("排序设置");
    cout << "设置查询结果中优先展示数额较大的收支" << endl;
    cout << "当前：";
    if (issortbiggeramount)cout << "是" << endl;
    else cout << "否" << endl;
    cout << "输入y更改为\"是\",输入n更改为\"否\",输入其它取消: ";
    string selection;
    cin >> selection;
    if (selection == "y" || selection == "Y")issortbiggeramount = true;
    else if (selection == "n" || selection == "N")issortbiggeramount = false;
    else {
        cout << "取消了操作" << endl;
        system("pause");
        selectmenu();
        return;
    }
    cout << "修改设置成功" << endl;
    system("pause");
    selectmenu();
    return;
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

    issortincome = true;issortnamefirst = false;   //排序参数
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
            cout << "No." << i + 1 << endl;
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
    cout << "请输入待查姓名(输入*代表查询全部):";
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
    cout << endl << "请输入待查年份(输入-1代表查询全部):";
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
    cout << endl << "请输入待查月份(输入-1代表查询全部):";
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
    double sumexpense = 0;
    vector<FinanceItem>queryresult;

    issortincome = false; issortnamefirst = false;   //排序参数
    sort(FinanceBook.begin(), FinanceBook.end(), cmp);  //结构体排序

    for (int i = 0; i < FinanceBook.size(); ++i) {
        if (FinanceBook[i].type != targetinfo.type)break;
        if (targetinfo.year == -1 || FinanceBook[i].year == targetinfo.year) {
            if (targetinfo.month == -1 || FinanceBook[i].month == targetinfo.month) {
                if (targetinfo.name == "*" || FinanceBook[i].name == targetinfo.name) {
                    queryresult.push_back(FinanceBook[i]);
                    sumexpense += FinanceBook[i].money;
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
            cout << "No." << i + 1 << endl;
            cout << "支出:" << fixed << setprecision(2) << queryresult[i].money << "元" << endl
                << "备注:" << queryresult[i].detail << endl << "------------------" << endl;
        }



    }
    if (sumexpense != 0)cout << endl << "共计:" << sumexpense << "元" << endl;
    if (queryresult.size() != 0)cout << queryresult.size() << "条记录" << endl;
    cout << "------------------" << endl;
    system("pause");
    selectmenu();

}

void exporttable() {
    FinanceItem targetinfo;
    string confirmation = "";

    clearFinanceItem(targetinfo);    //Initialize it
    targetinfo.type = 1;    //此处是收入
    system("cls");  //清屏
    printtitle("打印报表");
    inputquerycondition(targetinfo);

    bool flag = false;
    double sumincome = 0;
    vector<FinanceItem>queryresult;

    issortincome = true;  issortnamefirst = false;    //排序参数
    sort(FinanceBook.begin(), FinanceBook.end(), cmp);  //结构体排序

    for (int i = 0; i < FinanceBook.size(); ++i) {
        
        if (targetinfo.year == -1 || FinanceBook[i].year == targetinfo.year) {
            if (targetinfo.month == -1 || FinanceBook[i].month == targetinfo.month) {
                if (targetinfo.name == "*" || FinanceBook[i].name == targetinfo.name) {
                    queryresult.push_back(FinanceBook[i]);
                    sumincome += (FinanceBook[i].type * FinanceBook[i].money);
                    flag = true;
                }
            }
            
        }
        
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
            cout << "No." << i + 1 << endl;
            if (queryresult[i].type == 1)cout << "收入:";
            else cout << "支出:";
            cout<< fixed << setprecision(2) << queryresult[i].money << "元" << endl
                << "备注:" << queryresult[i].detail << endl << "------------------" << endl;
        }



    }
    if (sumincome != 0)cout << endl << "共计变化:" <<showpos<< sumincome <<noshowpos<< "元" << endl;
    if (queryresult.size() != 0)cout << queryresult.size() << "条记录" << endl;
    cout << "------------------" << endl;
    time_t now = time(0);  //声明time_t类型变量
    struct tm* t = localtime(&now);//获取系统日期和时间
    sysyear = 1900 + t->tm_year;
    sysmonth = 1 + t->tm_mon;
    //struct tm t;   //tm结构指针
    //time_t now;  //声明time_t类型变量
    //time(&now);      //获取系统日期和时间
    //localtime_s(&t, &now);
    /*exporttofile(queryresult, sumincome,t);*/
    exporttofile(queryresult, sumincome, *t);
    system("pause");
    selectmenu();
}

string gettimestr(tm t,int mode) {
    string tmpstr = "";
    if (mode == 0) {
        tmpstr += to_string(t.tm_year + 1900);
        tmpstr += "-";
        tmpstr += to_string(t.tm_mon + 1);
        tmpstr += "-";
        tmpstr += to_string(t.tm_mday);
        tmpstr += " ";
        tmpstr += to_string(t.tm_hour);
        tmpstr += "_";
        if (t.tm_min < 10)tmpstr += "0";
        tmpstr += to_string(t.tm_min);
        tmpstr += "_";
        if (t.tm_sec < 10)tmpstr += "0";
        tmpstr += to_string(t.tm_sec);
    }
    else {
        tmpstr += to_string(t.tm_year + 1900);
        tmpstr += "-";
        tmpstr += to_string(t.tm_mon + 1);
        tmpstr += "-";
        tmpstr += to_string(t.tm_mday);
        tmpstr += " ";
        tmpstr += to_string(t.tm_hour);
        tmpstr += ":";
        if (t.tm_min < 10)tmpstr += "0";
        tmpstr += to_string(t.tm_min);
        tmpstr += ":";
        if (t.tm_sec < 10)tmpstr += "0";
        tmpstr += to_string(t.tm_sec);
    }
    return tmpstr;
}

void exporttofile(vector<FinanceItem> queryresult,double sum,tm t) {
    cout << "导出中..." << endl;
    ofstream output("Export_"+ gettimestr(t, 0) +".txt", ios_base::binary);
    if (output.fail()) {
        cout << "打开文件失败！" << endl;
        return;
    }
    
    output << "家庭财务管理系统" << endl << gettimestr(t, 1);


    output << endl << "----[查询结果]----";
    if (queryresult.size() == 0) {
        output << endl << endl << "无结果" << endl << endl;
    }
    else {
        issortnamefirst = true;
        sort(queryresult.begin(), queryresult.end(), cmp);

        string currentname = ""; int currentyear = 0; int currentmonth = 0;
        for (int i = 0; i < queryresult.size(); i++)
        {

            if (currentname != queryresult[i].name) {
                output << endl << endl << "姓名:" << queryresult[i].name << endl;
                currentname = queryresult[i].name;
                currentyear = 0; currentmonth = 0;
            }
            if (currentyear != queryresult[i].year || currentmonth != queryresult[i].month) {
                currentyear = queryresult[i].year;
                currentmonth = queryresult[i].month;
                output << endl << "时间:" << queryresult[i].year << "/" << queryresult[i].month << endl
                    << "------------------" << endl;
            }
            output << "No." << i + 1 << endl;
            if (queryresult[i].type == 1)output << "收入:";
            else output << "支出:";
            output << fixed << setprecision(2) << queryresult[i].money << "元" << endl
                << "备注:" << queryresult[i].detail << endl << "------------------" << endl;
        }



    }
    if (sum != 0)output << endl << "共计变化:" <<showpos<< sum << noshowpos <<"元" << endl;
    if (queryresult.size() != 0)output << queryresult.size() << "条记录" << endl;
    output << "------------------" << endl;
    output.close();
    cout << "已成功导出到" << "Export_" << gettimestr(t, 0) << ".txt" <<endl;
}

void showabout() {
    system("cls");  //清屏
    printtitle("关于程序");
    cout << "家庭财务管理系统" << endl
        << "版本 1.0.0" << endl << endl
        << "A SHU ALP Course Project" << endl << endl
        << "Authors" << endl<<endl
        << "hidacow      黄　浩 20122971 (Leader)" << endl
        << "Davidguess   黄永橙 20122967 (Member)" << endl
        << "medicalpants 于俊勇 20122969 (Member)" << endl
        << "Ch-franck    黄星宇 20122970 (Member)" << endl
        << endl << endl
        << "Github:" << endl<<endl
        << "https://github.com/hidacow/FamilyFinanceManager" << endl<<endl<<endl;
   system("pause");
   selectmenu();

}
