//
// Created by HP on 2022/9/5.
//
//#include<iostream>
//
//using namespace std;
//
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
//    SqList(const ElemType *arr, int size);
//
//    virtual ~SqList();//析构函数
//    int Length() const;//返回顺序表长度
//    bool Empty() const;//判断顺序表是否为空
//    void Clear();//清空顺序表
//    ElemType GetElem(int pos) const;//返回指定位置的元素
//    void SetElem(int pos, const ElemType &key);//设置指定位置的元素
//    void Delete(int pos);//删除指定位置的元素
//    void Insert(int pos, const ElemType &key);//在指定位置插入指定的值
//    bool Find(ElemType key);
//
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
//SqList<ElemType>::SqList(const ElemType *arr, int size) {
//    maxSize = size;
//    sqList = new ElemType[maxSize];
//    for (count = 0; count < size; count++) {
//        sqList[count] = arr[count];
//    }
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
//    if (&copy != this) {
//        count = copy.count;
//        maxSize = copy.maxSize;
//        sqList = new ElemType[maxSize];
//        for (int i = 0; i < copy.maxSize; i++) {
//            sqList[i] = copy.sqList[i];
//        }
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
//bool SqList<ElemType>::Find(ElemType key) {
//    for (int i = 0; i < count; i++) {
//        if (key == sqList[i]) {
//            return true;
//        }
//    }
//    return false;
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
//
//int main() {
//    SqList<int> list(10);
//    for (int i = 1; i <= 10; i++) {
//        list.Insert(i, i);
//    }
//    Print(list);
//    int leftPos = 1;
//    int rightPos = list.Length();
//    while (leftPos <= rightPos) {
//        if (list.GetElem(leftPos) % 2 == 1) {
//            leftPos++;
//        }
//        if (list.GetElem(rightPos) % 2 == 0) {
//            rightPos--;
//        }
//        if (list.GetElem(leftPos) % 2 == 0 && list.GetElem(rightPos) % 2 == 1) {
//            int temp = list.GetElem(leftPos);
//            list.SetElem(leftPos, list.GetElem(rightPos));
//            list.SetElem(rightPos, temp);
//            leftPos++;
//            rightPos--;
//        }
//    }
//    Print(list);
//    return 0;
//}

//int main() {
//    int arr[10] = {1, 2, 5, 3, 6, 9, 10, 7, 13, 21};
//    int brr[10] = {1, 3, 7, 9, 2, 33, 14, 5, 0, 20};
//    SqList<int> a(arr, 10), b(brr, 10), c(10);
//    Print(a);
//    Print(b);
//    int cnt = 1;
//    for (int i = 0; i < a.Length(); i++) {
//        if (!b.Find(a.GetElem(i + 1))) {
//            c.Insert(cnt++, a.GetElem(i + 1));
//        }
//    }
//    Print(c);
//    return 0;
//}

//int main() {
//    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//    SqList<int> target(arr, 10), even(10), odd(10);
//    for (int i = 1; i <= target.Length(); i++) {
//        if (target.GetElem(i) % 2 == 1) {
//            odd.Insert(odd.Length() + 1, target.GetElem(i));
//        } else {
//            even.Insert(even.Length() + 1, target.GetElem(i));
//        }
//    }
//    Print(odd);
//    Print(even);
//    target.Clear();
//    for (int i = 1; i <= odd.Length(); i++) {
//        target.Insert(target.Length() + 1, odd.GetElem(i));
//    }
//    for (int j = 1; j <= even.Length(); j++) {
//        target.Insert(target.Length() + 1, even.GetElem(j));
//    }
//    Print(target);
//    return 0;
//}

//#include<iostream>
//#include "test.hpp"
//
//using namespace std;
//
//int main() {
//    Test<int> t(10);
//    cout << t.Get() << '\n';
//    t.Set(20);
//    cout << t.Get() << '\n';
//    return 0;
//}


//链表

//#include<iostream>
//
//using namespace std;
//
//template<class ElemType>
//struct Node {
//    ElemType data;
//    Node<ElemType> *next;
//
//    Node();
//
//    explicit Node(ElemType item, Node<ElemType> *link = NULL);
//};
//
//template<class ElemType>
//Node<ElemType>::Node() {
//    next = NULL;//指针域初始化为空
//}
//
//template<class ElemType>
//Node<ElemType>::Node(ElemType item, Node<ElemType> *link) {
//    data = item;
//    next = link;
//}
//
//template<class ElemType>
//class SimpleLinkList {
//protected:
//    Node<ElemType> *head;
//
//    //辅助函数
//    Node<ElemType> *GetElemPtr(int pos) const;//返回第pos个结点的指针
//
//public:
//    SimpleLinkList();
//
//    virtual ~SimpleLinkList();
//
//    int Length() const;
//
//    bool Empty() const;
//
//    void Clear();
//
//    void Traverse(void(*Visit)(ElemType &));
//
//    ElemType GetElem(int pos) const;
//
//    void SetElem(int pos, ElemType key);
//
//    void Delete(int pos);
//
//    void Insert(int pos, ElemType key);
//
//    SimpleLinkList(const SimpleLinkList<ElemType> &copy);
//
//    SimpleLinkList<ElemType> &operator=(const SimpleLinkList<ElemType> &copy);
//};
//
//template<class ElemType>
//Node<ElemType> *SimpleLinkList<ElemType>::GetElemPtr(int pos) const {
//    Node<ElemType> *node = head;
//    int curPos = 0;
//    while (node != NULL && curPos != pos) {
//        node = node->next;
//        curPos++;
//    }
//    if (node != NULL && curPos == pos) {
//        //查找成功
//        return node;
//    } else {
//        //查找失败
//        return NULL;
//    }
//}
//
//template<class ElemType>
//SimpleLinkList<ElemType>::SimpleLinkList() {
//    head = new Node<ElemType>;
//}
//
//template<class ElemType>
//int SimpleLinkList<ElemType>::Length() const {
//    int count = 0;
//    Node<ElemType> *tmpPtr = head->next;
//    while (tmpPtr != NULL) {
//        count++;
//        tmpPtr = tmpPtr->next;
//    }
//    return count;
//}
//
//template<class ElemType>
//bool SimpleLinkList<ElemType>::Empty() const {
//    return head->next == NULL;
//}
//
//template<class ElemType>
//void SimpleLinkList<ElemType>::Clear() {
//    while (Length() > 0) {
//        Delete(1);//不停删除第一个结点，直到链表为空
//    }
//}
//
//template<class ElemType>
//void SimpleLinkList<ElemType>::Traverse(void(*Visit)(ElemType &)) {
//    for (int i = 1; i <= Length(); i++) {
//        Node<ElemType> *tmpPtr = GetElemPtr(i);
//        Visit(tmpPtr->data);
//    }
//}
//
//template<class ElemType>
//ElemType SimpleLinkList<ElemType>::GetElem(int pos) const {
//    if (pos < 1 || pos > Length()) {
//        cout << "位置错误\n";
//        exit(0);
//    } else {
//        Node<ElemType> *tmpPtr = GetElemPtr(pos);
//        return tmpPtr->data;
//    }
//}
//
//template<class ElemType>
//void SimpleLinkList<ElemType>::SetElem(int pos, ElemType key) {
//    if (pos < 1 || pos > Length()) {
//        cout << "位置错误\n";
//        exit(0);
//    } else {
//        Node<ElemType> *tmpPtr = GetElemPtr(pos);
//        tmpPtr->data = key;
//    }
//
//}
//
//template<class ElemType>
//void SimpleLinkList<ElemType>::Insert(int pos, ElemType key) {
//    if (pos < 1 || pos > Length() + 1) {
//        cout << "位置错误\n";
//        exit(0);
//    } else {
//        Node<ElemType> *newNode;
//        Node<ElemType> *tmpPtr;
//        tmpPtr = GetElemPtr(pos - 1);
//        newNode = new Node<ElemType>(key, tmpPtr->next);
//        tmpPtr->next = newNode;
//    }
//}
//
//template<class ElemType>
//void SimpleLinkList<ElemType>::Delete(int pos) {
//    if (pos < 1 || pos > Length()) {
//        cout << "位置错误\n";
//        exit(0);
//    } else {
//        Node<ElemType> *tmpPtr = GetElemPtr(pos - 1);
//        Node<ElemType> *nextPtr = tmpPtr->next;
//        tmpPtr->next = nextPtr->next;
//        delete nextPtr;
//    }
//}
//
//template<class ElemType>
//SimpleLinkList<ElemType>::SimpleLinkList(const SimpleLinkList<ElemType> &copy) {
//    head = copy.head;
//}
//
//template<class ElemType>
//SimpleLinkList<ElemType>::~SimpleLinkList() {
//    delete head;
//}
//
//template<class ElemType>
//SimpleLinkList<ElemType> &SimpleLinkList<ElemType>::operator=(const SimpleLinkList<ElemType> &copy) {
//    if (&copy != this) {
//        head = copy.head;
//    }
//    return *this;
//}
//
//
//template<class ElemType>
//void Print(ElemType val) {
//    cout << val << ' ';
//}
//
//template<class ElemType>
//void Reverse(SimpleLinkList<ElemType> &list) {
//    for (int i = 1; i <= list.Length() / 2; i++) {
//        ElemType aItem = list.GetElem(i);
//        ElemType bItem = list.GetElem(list.Length() - i + 1);
//        list.SetElem(i, bItem);
//        list.SetElem(list.Length() - i + 1, aItem);
//    }
//}
//
//int main() {
//    /*归并la,lb到lc（la,lb为有序递增链表，要保证lc也是有序递增链表*/
//    SimpleLinkList<int> la, lb, lc;
//    for (int i = 1; i <= 5; i++) {
//        la.Insert(i, 2 * i - 1);
//        lb.Insert(i, 2 * i);
//    }
//    la.Traverse(Print);
//    putchar('\n');
//    lb.Traverse(Print);
//    putchar('\n');
//    int curPos = 0, aPos = 1, bPos = 1;
//    while (aPos <= la.Length() && bPos <= lb.Length()) {
//        if (la.GetElem(aPos) < lb.GetElem(bPos)) {
//            lc.Insert(++curPos, la.GetElem(aPos));
//            aPos++;
//        } else if (la.GetElem(aPos) > lb.GetElem(bPos)) {
//            lc.Insert(++curPos, lb.GetElem(bPos));
//            bPos++;
//        }
//    }
//    while (aPos <= 5) {
//        lc.Insert(++curPos, la.GetElem(aPos));
//        aPos++;
//    }
//    while (bPos <= 5) {
//        lc.Insert(++curPos, lb.GetElem(bPos));
//        bPos++;
//    }
//    lc.Traverse(Print);
//    putchar('\n');
//
//    /* 翻转链表 */
//    SimpleLinkList<int> la;
//    for (int i = 1; i <= 10; i++) {
//        la.Insert(i, i);
//    }
//    la.Traverse(Print);
//    putchar('\n');
//    Reverse(la);
//    la.Traverse(Print);
//    return 0;
//}
