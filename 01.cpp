//
// Created by HP on 2022/9/3.
//
// ???????????????1/0?
// ?? --- ??
//????
//#include<iostream>
//#include<time.h>
//#include<cstdlib>
//#include<windows.h>
//
//using namespace std;
//const int MAXN = 10;
//int matrix[MAXN][MAXN];
//
//void Show() {
//    for (int i = 0; i < MAXN; i++) {
//        for (int j = 0; j < MAXN; j++) {
//            if (matrix[i][j] == 1) {
//                putchar('*');
//                putchar(' ');
//                putchar(' ');
//            } else {
//                putchar('-');
//                putchar(' ');
//                putchar(' ');
//            }
//        }
//        putchar('\n');
//    }
//}
//
//void Check(int x, int y) {
//    int cnt = 0;
//    for (int i = x - 1; i <= x + 1; i++) {
//        if (i < 0 || i >= MAXN) {
//            continue;
//        }
//        for (int j = y - 1; j <= y + 1; j++) {
//            if (j < 0 || j >= MAXN) {
//                continue;
//            }
//            cnt += matrix[i][j];
//        }
//    }
//    matrix[x][y] = (cnt <= 1 || cnt > 3) ? 0 : 1;
//}
//
//int main() {
//    srand((unsigned int) time(NULL));
//    for (int i = 0; i < MAXN; i++) {
//        for (int j = 0; j < MAXN; j++) {
//            matrix[i][j] = rand() % 2;//??1??0????
//        }
//    }
//
//    while (1) {
//        system("cls");
//        for (int i = 0; i < MAXN; i++) {
//            for (int j = 0; j < MAXN; j++) {
//                Check(i, j);
//            }
//        }
//        Show();
//        Sleep(500);
//    }
//    return 0;
//}


//#include<iostream>
//#include<time.h>
//#include<cstdlib>
//#include<conio.h>
//
//using namespace std;
//const char *s[3] = {"石头", "剪刀", "布"};
//
//bool Game() {
//    int computer = rand() % 3 + 1;
//    int player;
//    char temp;
//    cout << "请出拳(1 --- 石头; 2 --- 剪刀; 3 --- 布): \n";
//    temp = getch();
//    player = temp - '0';
//    cout << "玩家: " << s[player - 1] << '\n';
//    cout << "电脑: " << s[computer - 1] << '\n';
//    if (computer == player) {
//        cout << "平局\n";
//    } else if (player == 3 && computer == 1) {
//        cout << "玩家胜利\n";
//    } else if (computer == 3 && player == 1) {
//        cout << "电脑胜利\n";
//    } else if (player < computer) {
//        cout << "玩家胜利\n";
//    } else if (computer < player) {
//        cout << "电脑胜利\n";
//    }
//
//    cout << "是否继续？(Y/N): \n";
//    bool ifContinue = tolower(getchar()) == 'y' ? true : false;
//    getchar();
//    return ifContinue;
//}
//
//int main() {
//    srand((unsigned) time(NULL));
//    bool active = true;
//    while (active) {
//        active = Game();
//    }
//    system("pause");
//    return 0;
//}

//#include <iostream>
//#include <string>
//#include <conio.h>
//using namespace std;
////i用来判断输入错误的次数
//int main()
//{
//    int i=0;
//    //初始化一个空字符串,s是密码字符串
//    string pwd="",s="123456";
//    cout<<"input password:";
//    char c;
//    while(true)
//    {
//        c=getch();
//        if(c!=13)//如果不是回车，就不断往string类型的pwd内添加c
//        {
//            pwd=pwd+c;
//            cout<<"*";
//        }else{
//            if(pwd==s)
//            {
//                cout<<"Yes!"<<endl;
//                break;
//            }else{
//                ++i;
//                if(i==3){
//                    cout<<"Dead!";
//                    break;
//                }else{
//                    cout<<"Wrong：Try Again!"<<endl;
//                    pwd="";
//                }
//            }
//        }
//    }
//}

//顺序表实现线性表


//#include<iostream>
//
//using namespace std;
//const int DEFAULT_N = 20;
//
//template<class ElemType>
//class SqList {
//protected:
//    int count;//顺序表中的元素个数
//    int maxSize;//顺序表最大元素个数
//    ElemType *sqList;
//
//    //辅助函数
//    bool Full() const;//判断线性表是否已满
//public:
//    explicit SqList(int size = DEFAULT_N);//构造函数   explicit关键字 --- 避免隐式类型转换
//    SqList(const SqList<ElemType> &copy);//拷贝构造函数
//    virtual ~SqList();//析构函数
//    int Length() const;//返回顺序表长度
//    bool Empty() const;//判断顺序表是否为空
//    void Clear();//清空顺序表
//    ElemType GetElem(int pos) const;//返回指定位置的元素
//    void SetElem(int pos, const ElemType &key);//设置指定位置的元素
//    void Delete(int pos);//删除指定位置的元素
//    void Insert(int pos, const ElemType &key);//在指定位置插入指定的值
//    SqList<ElemType> &operator=(const SqList<ElemType> &copy);//重载赋值运算符
//};
//
//template<class ElemType>
//bool SqList<ElemType>::Full() const {
//    return count == maxSize;
//}
//
//template<class ElemType>
//SqList<ElemType>::SqList(int size) {
//    count = 0;
//    maxSize = size;
//    sqList = new ElemType[maxSize];
//}
//
//template<class ElemType>
//int SqList<ElemType>::Length() const {
//    return count;
//}
//
//template<class ElemType>
//bool SqList<ElemType>::Empty() const {
//    return count == 0;
//}
//
//template<class ElemType>
//void SqList<ElemType>::Clear() {
//    count = 0;
//}
//
//template<class ElemType>
//ElemType SqList<ElemType>::GetElem(int pos) const {
//    if (pos < 1 || pos > count) {
//        cout << "位置错误\n";
//        return 0;
//    } else {
//        return sqList[pos - 1];
//    }
//}
//
//template<class ElemType>
//void SqList<ElemType>::SetElem(int pos, const ElemType &key) {
//    if (pos < 1 || pos > count) {
//        cout << "位置错误\n";
//        return;
//    } else {
//        sqList[pos - 1] = key;
//    }
//}
//
//template<class ElemType>
//void SqList<ElemType>::Delete(int pos) {
//    if (Empty()) {
//        cout << "顺序表已经为空\n";
//        return;
//    } else if (pos < 1 || pos > count) {
//        cout << "位置错误\n";
//        return;
//    } else {
//        for (int i = pos - 1; i < count - 1; i++) {
//            sqList[i] = sqList[i + 1];
//        }
//        count--;
//    }
//}
//
//template<class ElemType>
//void SqList<ElemType>::Insert(int pos, const ElemType &key) {
//    if (Full()) {
//        cout << "顺序表已满\n";
//        return;
//    } else if (pos < 1 || pos > maxSize) {
//        cout << "位置错误\n";
//        return;
//    } else {
//        for (int i = count; i > pos; i--) {
//            sqList[i] = sqList[i - 1];
//        }
//        sqList[pos - 1] = key;
//        count++;
//    }
//}
//
//template<class ElemType>
//SqList<ElemType> &SqList<ElemType>::operator=(const SqList<ElemType> &copy) {
//    delete[] sqList;
//    count = copy.count;
//    maxSize = copy.maxSize;
//    sqList = new ElemType[maxSize];
//    for (int i = 0; i < copy.maxSize; i++) {
//        sqList[i] = copy.sqList[i];
//    }
//    return *this;
//}
//
//template<class ElemType>
//SqList<ElemType>::SqList(const SqList<ElemType> &copy) {
//    count = copy.count;
//    maxSize = copy.maxSize;
//    sqList = new ElemType[maxSize];
//    for (int i = 0; i < copy.maxSize; i++) {
//        sqList[i] = copy.sqList[i];
//    }
//}
//
//template<class ElemType>
//SqList<ElemType>::~SqList() {
//    delete[] sqList;
//}
//
//template<class ElemType>
//void Print(const SqList<ElemType> &sl) {
//    for (int i = 1; i <= sl.Length(); i++) {
//        cout << sl.GetElem(i) << ' ';
//    }
//    putchar('\n');
//}
//
//int main() {
//    SqList<int> slint(10);
//    cout << slint.Length() << '\n';
//    for (int i = 1; i <= 5; i++) {
//        slint.Insert(i, i);
//    }
//    cout << slint.Length() << '\n';
//    Print(slint);
//    slint.Delete(1);
//    Print(slint);
//    return 0;
//}
