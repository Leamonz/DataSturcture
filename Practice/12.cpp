//
// Created by HP on 2022/9/25.
//
//#include "Matrix.h"
//#include<iostream>
//#include<iomanip>
//#include"MyList.h"
//
//using namespace std;
//
//template<class ElemType>
//void Print(ElemType &val) {
//    cout << val << ' ';
//}
//
//int main() {
//    SimpleLinkList<int> test;
//    for (int i = 1; i <= 10; i++) {
//        test.Insert(test.Length() + 1, i);
//    }
//    test.Traverse(Print);
//    cout << endl;
//    test.reverse();
//    test.Traverse(Print);
//    cout << endl;
//    test.reverse();
//    test.Traverse(Print);
//    return 0;
//}

//template<class ElemType>
//void Print(const Matrix<ElemType> &mat) {
//    for (int i = 0; i < mat.GetRows(); i++) {
//        for (int j = 0; j < mat.GetCols(); j++) {
//            cout << setw(3) << mat(i, j) << ' ';
//        }
//        cout << endl;
//    }
//}
//
//int main() {
//    Matrix<int> test(5, 5);
//    for (int i = 0; i < test.GetRows(); i++) {
//        for (int j = 0; j < test.GetCols(); j++) {
//            test(i, j) = (i + 1) * (j + 1);
//        }
//    }
//    Print<int>(test);
//    Matrix<int> test1(test), test2;
//    cout << endl;
//    Print<int>(test1);
//    cout << endl;
//    test2 = test;
//    Print(test2);
//    return 0;
//}


//#include"MyList.h"//链表类所在头文件
//#include<iostream>
//
//using namespace std;
//
//template<class ElemType>
//void Merge(const SimpleLinkList<ElemType> &la, const SimpleLinkList<ElemType> &lb, SimpleLinkList<ElemType> &lc) {
//    //单向链表
//    //思路：先把元素按递增顺序放入lc中，然后翻转链表lc
//    int aPos = 1, bPos = 1;
//    ElemType aItem, bItem;
//    aItem = la.GetElem(aPos);
//    bItem = lb.GetElem(bPos);
//    while (aPos <= la.Length() && bPos <= lb.Length()) {
//        aItem = la.GetElem(aPos);
//        bItem = lb.GetElem(bPos);
//        if (aItem < bItem) {
//            lc.Insert(lc.Length() + 1, aItem);
//            aPos++;
//        } else if (aItem > bItem) {
//            lc.Insert(lc.Length() + 1, bItem);
//            bPos++;
//        } else {
//            lc.Insert(lc.Length() + 1, aItem);
//            aPos++;
//            bPos++;
//        }
//    }
//    while (aPos <= la.Length()) {
//        aItem = la.GetElem(aPos);
//        if (aItem != lc.GetElem(lc.Length())) {
//            lc.Insert(lc.Length() + 1, aItem);
//        }
//        aPos++;
//    }
//    while (bPos <= lb.Length()) {
//        bItem = lb.GetElem(bPos);
//        if (bItem != lc.GetElem(lc.Length())) {
//            lc.Insert(lc.Length() + 1, bItem);
//        }
//        bPos++;
//    }
//    lc.reverse();//反转链表
//}
//
//template<class ElemType>
//void Print(ElemType &val) {
//    cout << val << ' ';
//}

//int main() {
//    SimpleLinkList<int> la, lb, lc;
//    la.Insert(1, 2);
//    la.Insert(2, 4);
//    la.Insert(3, 5);
//
//    lb.Insert(1, 1);
//    lb.Insert(2, 3);
//    lb.Insert(3, 4);
//    lb.Insert(4, 7);
//    Merge(la, lb, lc);
//    lc.Traverse(Print);
//    return 0;
//}