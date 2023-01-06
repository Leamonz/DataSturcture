//
// Created by HP on 2022/9/23.
//
//#include<iostream>
//
//using namespace std;
//
//int main() {
//    int a = 5, &b = a;
//    int c = b;
//    cout << c << endl;
//    return 0;
//}
//
//#include<iostream>
////可变长参数需要用到的宏在该头文件中定义
//#include<cstdarg>
//#include<cstring>
//
//using namespace std;

// ... 表明该函数使用可变长参数
//int my_sum(int count, ...) {
//    int sum = 0;
//    //定义可变长参数列表
//    va_list args;
//    //开始使用可变长参数列表，第二个参数为可变长参数前的最后一个固定参数
//    va_start(args, count);
//    for (int i = 0; i < count; i++) {
//        //利用va_arg()依次访问可变长参数列表中的参数，第二个参数表示访问的参数类型
//        sum += va_arg(args, int);
//    }
//    //最后一定要使用的宏，表明结束使用可变长参数列表
//    va_end(args);
//    return sum;
//}
//
//int find(int count, const char *target, ...) {
//    int find = -1, key = -1;
//    const char *s;
//    va_list args;
//    va_start(args, target);
//    for (int i = 0; i < count; i++) {
//        key = va_arg(args, int);
//        s = va_arg(args, const char*);
//        if (strcmp(target, s) == 0) {
//            find = key;
//            break;
//        }
//    }
//    return find;
//}
//
//int main() {
////    cout << my_sum(4, 1, 2, 3, 4) << endl;
//    const char *ss = "hello";
//    int tar = 50;
//    cout << find(3, "hello", 20, "world", 40, "hubert", tar, ss) << endl;
//    return 0;
//}

//#include "Array.h"
//#include<iostream>
//
//using namespace std;
//
//int main() {
//    Array<int> test(2, 2, 2);
//    for (int i = 0; i < 2; i++) {
//        for (int j = 0; j < 2; j++) {
//            test(i, j) = (i + 1) * (j + 1);
//        }
//    }
//    for (int i = 0; i < 2; i++) {
//        for (int j = 0; j < 2; j++) {
//            cout << test(i, j) << ' ';
//        }
//        cout << endl;
//    }
//    return 0;
//}
