//
// Created by HP on 2022/10/1.
//
//#include "Node.hpp"
//#include "SingleLinkedList.hpp"
//#include<iostream>

//using namespace std;

//int main() {
//    SingleLinkedList<int> test;
//    for (int i = 0; i < 5; i++) {
//        test.insert(i + 1, test.length());
//    }
//    int elem;
//    for (int i = 0; i < 5; i++) {
//        test.get(i, elem);
//        cout << elem << ' ';
//    }
//    cout << endl;
////    test.deleteElem(4);
////    test.deleteElem(3);
////    test.deleteElem(2);
////    test.deleteElem(1);
////    test.get(0, elem);
////    cout << elem << endl;
////    test.deleteElem(0);
//    cout << test.empty() << endl;
////    test.clear();
////    cout << test.empty() << endl;
//    cout << test[100];
//    return 0;
//}

//#include <iostream>                         // 包含输入输出接口文件
//using namespace std;
//int main()                                  // 定义主函数
//{                                           // 主函数开始
//    char choice;                            // 模块号（字符）
//    int nChoice;                            // 模块号（数字）
//    system("cls");
//    cout<<"\n\n\n\n\n";
//    cout<<"\t\t|---------------学生选课系统(学生版)------------|\n";
//    cout<<"\t\t|\t 0. 返回                               |\n";
//    cout<<"\t\t|\t 1. 学生信息管理                       |\n";
//    cout<<"\t\t|\t 2. 教师信息信息                       |\n";
//    cout<<"\t\t|\t 3. 课程信息管理                       |\n";
//    cout<<"\t\t|\t 4. 学生选课信息                       |\n";
//    cout<<"\t\t|\t 5. 学生成绩管理                       |\n";
//    cout<<"\t\t|\t 6. 信息统计模块                       |\n";
//    cout<<"\t\t|-----------------------------------------------|\n\n";
//    cout<<"\t\t\t请输入模块编号(0-6):";
//    cin>>choice;                            // 输入字符模块号
//    if(choice < '0' || choice > '9')        // 输入的模块号不是数字
//      {
//          cout<<"模块号应为数字！"<<endl;
//          return 1;                          // 模块号不正确，返回错误代码
//      }
//    nChoice = choice - '0';                // 将字符模块号转为数字
//    switch(nChoice)
//    {
//        case 0:
//            cout<<"你输入的模块名称为：0. 返回"<<endl;
//            break;
//        case 1:
//            cout<<"你输入的模块名称为：1. 学生信息管理"<<endl;
//            break;
//        case 2:
//            cout<<"你输入的模块名称为：2. 教师信息信息"<<endl;
//            break;
//        case 3:
//            cout<<"你输入的模块名称为：3. 课程信息管理"<<endl;
//            break;
//        case 4:
//            cout<<"你输入的模块名称为：4. 学生选课信息"<<endl;
//            break;
//        case 5:
//            cout<<"你输入的模块名称为：5. 学生成绩管理"<<endl;
//            break;
//        case 6:
//            cout<<"你输入的模块名称为：6. 信息统计模块"<<endl;
//            break;
//        default:
//            cout<<"你输入的模块不存在！"<<endl;
//    }
//    return 0;
//}                                           // 主函数结束
