# FamilyFinanceManager
## Introduction
    家庭财务管理系统旨在给家庭成员提供一个管理家庭财务的平台，主要对家庭成员的收入和支出进行增删改查操作，此时不考虑收入为负值的情况，并能统计总收入与总支出。
## Function
### 初始化菜单
    程序开始运行后显示菜单，要求菜单能完全展示本系统的功能，尽力做到设计美观。
###	选择待操作的文件
    考虑到本系统有多个文件，需要提示用户输入来选择需要操作的文件是家庭成员收入信息还是家庭总支出信息。
###	查询家庭成员收入信息与家庭支出信息
    选择相应的家庭成员文件，按月份查询此家庭成员的收入信息。提示用户输入待查月份，显示相应月份的收入信息。如果没有满足要求的月份，输出提示信息。
    可输出此家庭成员全部收入信息，若当前家庭成员没有收入，输出提示信息。
    选择家庭支出信息文件后，按月份或支出项查询支出信息。提示用户输入待查的月份或者支出项，显示符合条件的支出信息。如果没有满足要求的支出，输出提示信息。
    可输出全部家庭支出信息，若当前家庭没有支出，输出提示信息。
###	删除支出信息
    按指定的月份、支出项删除家庭支出中对应记录，删除时应删除此项支出的所有信息并提示删除成功。若此支出项不存在，输出提示信息。
###	修改收入信息和支出信息
    修改某家庭成员的收入信息。选择对应的家庭成员后，提示用户输入要修改月份，若此月份存在，则提示选择修改此月收入。若该月份不存在，输出提示信息。
###	增加收入信息与支出信息
    通过控制台增加收入信息，选择家庭成员后，提示用户输入待增加的月份，如果月份存在，则在原有收入上增加收入；如果不存在，增加收入信息。
    通过控制台增加支出信息，提示用户输入支出的月份、支出项与支出金额。计算本月支出金额是否大于本月家庭总收入（暂时不考虑用之前月份的结余，就当以前的结余都进股市了），如果小于家庭总收入，则看此支出项十分存在，如果此支出项存在， 在原支出项上增加金额，如果不存在，创建支出项。如果超支，提示超支。
###	支出排序
    选择两种排序状态：月度排序与年度排序。从高到低输出月份（年度排序）、支出项与支出金额。
###	保存家庭成员收入信息与家庭支出信息
	将当前家庭成员收入信息与家庭支出信息分别保存到txt文件中。
### 退出系统
    用户可通过输入特定指令来退出程序，在用户输入退出指令之前，程序不得自行退出。
## Group Member
 - 黄浩
 - 黄永橙
 - 于俊勇
 - 黄星宇
