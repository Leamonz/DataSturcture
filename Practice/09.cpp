//
// Created by HP on 2022/9/18.
//

//#include"MyString.h"
//#include<iostream>
//#include"MyList.h"
//
//using namespace std;

//int main() {
//    MyString s("hello"), s1("world");
//    const char *temp = s.CStr();
////    cout << temp << endl;
////    cout << s << endl;
////    s = s1;
////    cout << temp << endl;
////    cout << s << endl;
//    Concat(s, s1);
//    cout << s << endl;
////    s1 = "hello";
////    cout << s1;
//
//    MyString s3;
//    cin >> s3;
//    cout << s3 << endl;
//    cout << Index(s3, MyString("ha")) << endl;
//    return 0;
//}

//template<class ElemType>
//void Print(ElemType &val) {
//    cout << val << ' ';
//}
//
//int main() {
////    SqList<int> test;
////    for (int i = 1; i <= 5; i++) {
////        test.Insert(i, i * 2);
////    }
////    for (int i = 1; i <= test.Length(); i++) {
////        int elem = test.GetElem(i);
////        cout << elem << ' ';
////    }
////    cout << endl;
////    SqList<int> test2(test), test3;
////    for (int i = 1; i <= test.Length(); i++) {
////        int elem = test2.GetElem(i);
////        cout << elem << ' ';
////    }
////    cout << endl;
////    test3 = test;
////    test3.SetElem(2, 14);
////    for (int i = 1; i <= test.Length(); i++) {
////        int elem = test3.GetElem(i);
////        cout << elem << ' ';
////    }
////    cout << endl;
////    for (int i = 1; i <= test.Length(); i++) {
////        int elem = test.GetElem(i);
////        cout << elem << ' ';
////    }
////    cout << endl;
//
////    SimpleLinkList<int> test1;
////    for (int i = 1; i <= 5; i++) {
////        test1.Insert(i, i);
////    }
////    for (int i = 1; i <= test1.Length(); i++) {
////        int elem = test1.GetElem(i);
////        cout << elem << ' ';
////    }
////    cout << endl;
////    SimpleLinkList<int> test2(test1), test3;
////    for (int i = 1; i <= test1.Length(); i++) {
////        int elem = test2.GetElem(i);
////        cout << elem << ' ';
////    }
////    cout << endl;
////
////    test3 = test1;
////    for (int i = 1; i <= test1.Length(); i++) {
////        int elem = test3.GetElem(i);
////        cout << elem << ' ';
////    }
////    cout << endl;
////    test3.SetElem(1, 10);
////    for (int i = 1; i <= test1.Length(); i++) {
////        int elem = test3.GetElem(i);
////        cout << elem << ' ';
////    }
////    cout << endl;
////    test1.Traverse(Print);
////    test3.Delete(3);
////    test3.Traverse(Print);
//
////    CircleLinkList<int> test1;
////    for (int i = 1; i <= 5; i++) {
////        test1.Insert(i, 10 * i);
////    }
////
////    test1.Traverse(Print);
////    cout << endl;
////    CircleLinkList<int> test2(test1), test3;
////    test2.Traverse(Print);
////    cout << endl;
////    test3 = test1;
////    test3.Traverse(Print);
////    cout << endl;
////
////    test3.SetElem(1, 100);
////    test3.Traverse(Print);
////    test1.Traverse(Print);
//
//
////    BiLinkList<int> test1;
////    for (int i = 1; i <= 5; i++) {
////        test1.Insert(i, i);
////    }
////    test1.Traverse(Print);
////    cout << endl;
////    BiLinkList<int> test2(test1);
////    test2.Traverse(Print);
////    cout << endl;
////    BiLinkList<int> test3;
////    test3 = test1;
////    test3.Traverse(Print);
////    cout << endl;
////    test3.SetElem(1, 10);
////    test3.Traverse(Print);
////    cout << endl;
////    test1.Traverse(Print);
////    cout << endl;
////    test1.SetElem(3, 30);
////    test1.Traverse(Print);
//    return 0;
//}

//#include<iostream>
//#include<cstring>
//
//using namespace std;
//
////字符串模式匹配
//int SimpleIndex(const char *target, const char *pattern, int pos = 0) {
//    int max_len = strlen(target);
//    int sub_len = strlen(pattern);
//    char *p1, *p2;
//    for (int i = pos; i <= max_len - sub_len; i++) {
//        p1 = (char *) target + i;
//        p2 = (char *) pattern;
//        while (*p1 == *p2 && *p2 != '\0') {
//            p1++;
//            p2++;
//        }
//        if (*p2 == '\0') {
//            return i;
//        }
//    }
//    //没有找到匹配子串
//    return -1;
//}
//
//int main() {
//    const char *a = "abdabcd";
//    const char *b = "abc";
//    cout << SimpleIndex(a, b) << endl;
//    return 0;
//}

//#include<iostream>
//#include<queue>
//using namespace std;
//int main() {
//    priority_queue<int, vector<int>, greater<int>> q;
//    int a;
//    for (int i = 0; i < 3; i++) {
//        cin >> a;
//        q.push(a);
//    }
//    for (int i = 0; i < 3; i++) {
//        a = q.top();
//        q.pop();
//        cout << a << ' ';
//    }
//    return 0;
//}