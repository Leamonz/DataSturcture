//
// Created by HP on 2022/9/19.
//

#ifndef CLION_MYLIST_H
#define CLION_MYLIST_H

#include<iostream>
#include"Node.h"

using namespace std;
const int DEFAULT_N = 20;

template<class ElemType>
class SqList {
protected:
    int count;//顺序表中的元素个数
    int maxSize;//顺序表最大元素个数
    ElemType *sqList;

    //辅助函数
    bool Full() const;//判断线性表是否已满
public:
    explicit SqList(int size = DEFAULT_N);//构造函数   explicit关键字 --- 避免隐式类型转换
    SqList(const SqList<ElemType> &copy);//拷贝构造函数
    virtual ~SqList();//析构函数
    int Length() const;//返回顺序表长度
    bool Empty() const;//判断顺序表是否为空
    void Clear();//清空顺序表
    void Traverse(void(*Visit)(ElemType &)) const;

    bool GetElem(int pos, ElemType &elem) const;//返回指定位置的元素
    bool SetElem(int pos, const ElemType &key);//设置指定位置的元素
    void Delete(int pos);//删除指定位置的元素
    void Insert(int pos, const ElemType &key);//在指定位置插入指定的值
    SqList<ElemType> &operator=(const SqList<ElemType> &copy);//重载赋值运算符
};

template<class ElemType>
bool SqList<ElemType>::Full() const {
    return count == maxSize;
}

template<class ElemType>
SqList<ElemType>::SqList(int size) {
    count = 0;
    maxSize = size;
    sqList = new ElemType[maxSize];
}

template<class ElemType>
int SqList<ElemType>::Length() const {
    return count;
}

template<class ElemType>
bool SqList<ElemType>::Empty() const {
    return count == 0;
}

template<class ElemType>
void SqList<ElemType>::Clear() {
    count = 0;
}

template<class ElemType>
void SqList<ElemType>::Traverse(void (*Visit)(ElemType &)) const {
    for (int i = 0; i < Length(); i++) {
        Visit(sqList[i]);
    }
}

template<class ElemType>
bool SqList<ElemType>::GetElem(int pos, ElemType &elem) const {
    if (pos < 1 || pos > Length()) {
        cout << "位置错误\n";
        return false;
    } else {
        elem = sqList[pos - 1];
        return true;
    }
}

template<class ElemType>
bool SqList<ElemType>::SetElem(int pos, const ElemType &key) {
    if (pos < 1 || pos > Length()) {
        cout << "位置错误\n";
        return false;
    } else {
        sqList[pos - 1] = key;
        return true;
    }
}

template<class ElemType>
void SqList<ElemType>::Delete(int pos) {
    if (Empty()) {
        cout << "顺序表已经为空\n";
        return;
    } else if (pos < 1 || pos > count) {
        cout << "位置错误\n";
        return;
    } else {
        for (int i = pos - 1; i < count - 1; i++) {
            sqList[i] = sqList[i + 1];
        }
        count--;
    }
}

template<class ElemType>
void SqList<ElemType>::Insert(int pos, const ElemType &key) {
    if (Full()) {
        cout << "顺序表已满\n";
        return;
    } else if (pos < 1 || pos > Length() + 1) {
        cout << "位置错误\n";
        return;
    } else {
        for (int i = count; i > pos; i--) {
            sqList[i] = sqList[i - 1];
        }
        sqList[pos - 1] = key;
        count++;
    }
}

template<class ElemType>
SqList<ElemType> &SqList<ElemType>::operator=(const SqList<ElemType> &copy) {
    if (&copy != this) {
        if (sqList != nullptr) {
            delete[] sqList;
            sqList = nullptr;
        }
        count = copy.count;
        maxSize = copy.maxSize;
        sqList = new ElemType[maxSize];
        for (int i = 0; i < count; i++) {
            sqList[i] = copy.sqList[i];
        }
    }
    return *this;
}

template<class ElemType>
SqList<ElemType>::SqList(const SqList<ElemType> &copy) {
    count = copy.count;
    maxSize = copy.maxSize;
    sqList = new ElemType[maxSize];
    for (int i = 0; i < count; i++) {
        sqList[i] = copy.sqList[i];
    }
}

template<class ElemType>
SqList<ElemType>::~SqList() {
    if (sqList != nullptr) {
        delete[] sqList;
        sqList = nullptr;
    }
}


//单向链表
template<class ElemType>
class SimpleLinkList {
protected:
    Node<ElemType> *head;
    mutable int curPos;
    mutable Node<ElemType> *curPtr;
    int count;

    //辅助函数
    Node<ElemType> *GetElemPtr(int pos) const;//返回第pos个结点的指针

public:
    SimpleLinkList();

    virtual ~SimpleLinkList();

    int Length() const;//返回链表长度

    bool Empty() const;//判空

    void Clear();//清空链表

    void Traverse(void(*Visit)(ElemType &)) const;//遍历链表元素并执行Visit函数

    bool GetElem(int pos, ElemType &elem) const;//获取pos上的元素

    bool SetElem(int pos, const ElemType &key);//改变pos上的元素

    void Delete(int pos);//删除pos上的元素

    void Insert(int pos, ElemType key);//在pos插入一个元素

    void reverse();//翻转链表

    SimpleLinkList(const SimpleLinkList<ElemType> &copy);//拷贝构造函数

    SimpleLinkList<ElemType> &operator=(const SimpleLinkList<ElemType> &copy);//重载赋值运算符
};

template<class ElemType>
Node<ElemType> *SimpleLinkList<ElemType>::GetElemPtr(int pos) const {
    if (pos < 0 || pos > Length()) {
        return nullptr;
    }
    if (curPos > pos) {
        curPtr = head;
        curPos = 0;
    }
    while (curPos != pos) {
        curPtr = curPtr->next;
        curPos++;
    }
    return curPtr;
//    Node<ElemType> *node = head;
//    int curPos = 0;
//    while (node != nullptr && curPos != pos) {
//        node = node->next;
//        curPos++;
//    }
//    if (node != nullptr && curPos == pos) {
//        //查找成功
//        return node;
//    } else {
//        //查找失败
//        return nullptr;
//    }
}

template<class ElemType>
SimpleLinkList<ElemType>::SimpleLinkList() {
    head = new Node<ElemType>();
    curPtr = head;
    curPos = 0;
    count = 0;
}

template<class ElemType>
int SimpleLinkList<ElemType>::Length() const {
//    int count = 0;
//    Node<ElemType> *tmpPtr = head->next;
//    while (tmpPtr != nullptr) {
//        count++;
//        tmpPtr = tmpPtr->next;
//    }
    return count;
}

template<class ElemType>
bool SimpleLinkList<ElemType>::Empty() const {
    return head->next == nullptr;
}

template<class ElemType>
void SimpleLinkList<ElemType>::Clear() {
    while (Length() > 0) {
        Delete(1);//不停删除第一个结点，直到链表为空
    }
}

template<class ElemType>
void SimpleLinkList<ElemType>::Traverse(void(*Visit)(ElemType &)) const {
    for (int i = 1; i <= Length(); i++) {
        Node<ElemType> *tmpPtr = GetElemPtr(i);
        Visit(tmpPtr->data);
    }
}

template<class ElemType>
bool SimpleLinkList<ElemType>::GetElem(int pos, ElemType &elem) const {
    if (pos < 1 || pos > Length()) {
        cout << "位置错误" << endl;
        return false;
    } else {
        Node<ElemType> *tmpPtr = GetElemPtr(pos);
        elem = tmpPtr->data;
        return true;
    }
}

template<class ElemType>
bool SimpleLinkList<ElemType>::SetElem(int pos, const ElemType &key) {
    if (pos < 1 || pos > Length()) {
        cout << "位置错误" << endl;
        return false;
    } else {
        Node<ElemType> *tmpPtr = GetElemPtr(pos);
        tmpPtr->data = key;
        return true;
    }

}

template<class ElemType>
void SimpleLinkList<ElemType>::Insert(int pos, ElemType key) {
    if (pos < 1 || pos > Length() + 1) {
        cout << "位置错误" << endl;
        return;
    } else {
        Node<ElemType> *newNode;
        Node<ElemType> *tmpPtr;
        tmpPtr = GetElemPtr(pos - 1);
        newNode = new Node<ElemType>(key, tmpPtr->next);
        tmpPtr->next = newNode;
        curPtr = newNode;
        curPos = pos;
        count++;
    }
}

template<class ElemType>
void SimpleLinkList<ElemType>::Delete(int pos) {
    if (pos < 1 || pos > Length()) {
        cout << "位置错误" << endl;
        return;
    } else {
        Node<ElemType> *prevPtr = GetElemPtr(pos - 1);
        Node<ElemType> *tmpPtr = prevPtr->next;
        prevPtr->next = tmpPtr->next;
        delete tmpPtr;
        count--;
    }
}

template<class ElemType>
void SimpleLinkList<ElemType>::reverse() {
    Node<ElemType> *tmpPtr = nullptr, *nextPtr = nullptr, *cur;
    cur = head->next;
    while (cur != nullptr) {
        tmpPtr = cur->next;
        cur->next = nextPtr;
        nextPtr = cur;
        cur = tmpPtr;
    }
    head->next = nextPtr;
    curPtr = head;
    curPos = 0;
}

template<class ElemType>
SimpleLinkList<ElemType>::SimpleLinkList(const SimpleLinkList<ElemType> &copy) {
    head = new Node<ElemType>();
    curPtr = head;
    curPos = 0;
    count = 0;
    Node<ElemType> *tmpPtr = copy.head->next;
    for (; tmpPtr != nullptr; tmpPtr = tmpPtr->next) {
        Insert(Length() + 1, tmpPtr->data);
    }
    curPtr = head;
    curPos = 0;
}

template<class ElemType>
SimpleLinkList<ElemType>::~SimpleLinkList() {
    Clear();
    delete head;
}

template<class ElemType>
SimpleLinkList<ElemType> &SimpleLinkList<ElemType>::operator=(const SimpleLinkList<ElemType> &copy) {
    if (&copy != this) {
        Clear();
        head = new Node<ElemType>();
        curPtr = head;
        curPos = 0;
        count = 0;
        Node<ElemType> *tmpPtr = copy.head->next;
        for (; tmpPtr != nullptr; tmpPtr = tmpPtr->next) {
            Insert(Length() + 1, tmpPtr->data);
        }
        curPtr = head;
        curPos = 0;
    }
    return *this;
}


//循环链表
template<class ElemType>
class CircleLinkList {
protected:
    Node<ElemType> *head;
    mutable Node<ElemType> *curPtr;
    mutable int curPos;
    int count = 0;

    //辅助函数
    Node<ElemType> *GetElemPtr(int pos) const;//返回第pos个结点的指针

public:
    CircleLinkList();

    virtual ~CircleLinkList();

    int Length() const;//返回链表长度

    bool Empty() const;//判空

    void Clear();// clear all elements in the list

    void Traverse(void(*Visit)(ElemType &)) const;//traverse the linklist by applying Visit function to all elements

    bool GetElem(int pos, ElemType &elem) const;//get the element on pos

    bool SetElem(int pos, const ElemType &key);//set the element on pos to key

    void Delete(int pos);//delete the element on pos

    void Insert(int pos, ElemType key);//insert an element with value key before pos

    CircleLinkList(const CircleLinkList<ElemType> &copy);//拷贝构造函数

    CircleLinkList<ElemType> &operator=(const CircleLinkList<ElemType> &copy);//重载赋值运算符
};

template<class ElemType>
Node<ElemType> *CircleLinkList<ElemType>::GetElemPtr(int pos) const {
    /*============================*/
    if (pos < 0 || pos > Length()) {
        return nullptr;
    }
    if (curPos > pos) {
        curPtr = head;
        curPos = 0;
    }
//    if (pos == 0) {
//        return head;
//    }
//    Node<ElemType> *tmpPtr = head->next;
//    int curPos = 1;
//    /*============================*/
//    while (tmpPtr != head && curPos != pos) {
//        tmpPtr = tmpPtr->next;
//        curPos++;
//    }
//    if (tmpPtr != head && curPos == pos) {
//        //查找成功
//        return tmpPtr;
//    } else {
//        //查找失败
//        return nullptr;
//    }
}

template<class ElemType>
CircleLinkList<ElemType>::CircleLinkList() {
    head = new Node<ElemType>();
    /*============================*/
    head->next = head;
    /*============================*/
    curPtr = head;
    curPos = 0;
    count = 0;
}

template<class ElemType>
int CircleLinkList<ElemType>::Length() const {
    return count;
//    int count = 0;
//    Node<ElemType> *tmpPtr = head->next;
//    /*============================*/
//    while (tmpPtr != head) {
//        /*============================*/
//        tmpPtr = tmpPtr->next;
//        count++;
//    }
//    return count;
}

template<class ElemType>
bool CircleLinkList<ElemType>::Empty() const {
    /*============================*/
    return head->next == head;
    /*============================*/
}

template<class ElemType>
void CircleLinkList<ElemType>::Clear() {
    while (Length() > 0) {
        Delete(1);//不停删除第一个结点，直到链表为空
    }
}

template<class ElemType>
void CircleLinkList<ElemType>::Traverse(void(*Visit)(ElemType &)) const {
    for (int i = 1; i <= Length(); i++) {
        Node<ElemType> *tmpPtr = GetElemPtr(i);
        Visit(tmpPtr->data);
    }
}

template<class ElemType>
bool CircleLinkList<ElemType>::GetElem(int pos, ElemType &elem) const {
    if (pos < 1 || pos > Length()) {
        cout << "位置错误" << endl;
        return false;
    } else {
        Node<ElemType> *tmpPtr = GetElemPtr(pos);
        elem = tmpPtr->data;
        return true;
    }
}

template<class ElemType>
bool CircleLinkList<ElemType>::SetElem(int pos, const ElemType &key) {
    if (pos < 1 || pos > Length()) {
        cout << "位置错误" << endl;
        return false;
    } else {
        Node<ElemType> *tmpPtr = GetElemPtr(pos);
        tmpPtr->data = key;
        return true;
    }
}

template<class ElemType>
void CircleLinkList<ElemType>::Insert(int pos, ElemType key) {
    if (pos < 1 || pos > Length() + 1) {
        cout << "位置错误" << endl;
        return;
    } else {
        Node<ElemType> *newNode;
        Node<ElemType> *tmpPtr;
        tmpPtr = GetElemPtr(pos - 1);
        newNode = new Node<ElemType>(key, tmpPtr->next);
        tmpPtr->next = newNode;
        curPtr = newNode;
        curPos = pos;
        count++;
    }
}

template<class ElemType>
void CircleLinkList<ElemType>::Delete(int pos) {
    if (pos < 1 || pos > Length()) {
        cout << "位置错误" << endl;
        return;
    } else {
        Node<ElemType> *prevPtr = GetElemPtr(pos - 1), *tmpPtr;
        tmpPtr = prevPtr->next;
        prevPtr->next = tmpPtr->next;
        delete tmpPtr;
        count--;
//        Node<ElemType> *tmpPtr = GetElemPtr(pos - 1);
//        Node<ElemType> *nextPtr = tmpPtr->next;//node to be deleted
//        tmpPtr->next = nextPtr->next;
//        delete nextPtr;
    }
}

template<class ElemType>
CircleLinkList<ElemType>::CircleLinkList(const CircleLinkList<ElemType> &copy) {
    head = new Node<ElemType>();
    head->next = head;
    curPtr = head;
    curPos = 0;
    count = 0;
    Node<ElemType> *tmpPtr = copy.head->next;
    for (; tmpPtr != copy.head; tmpPtr = tmpPtr->next) {
        Insert(Length() + 1, tmpPtr->data);
    }
    curPtr = head;
    curPos = 0;
}

template<class ElemType>
CircleLinkList<ElemType>::~CircleLinkList() {
    Clear();
    delete head;
}

template<class ElemType>
CircleLinkList<ElemType> &CircleLinkList<ElemType>::operator=(const CircleLinkList<ElemType> &copy) {
    if (&copy != this) {
        Clear();
        head = new Node<ElemType>;
        head->next = head;
        curPtr = head;
        curPos = 0;
        count = 0;
        Node<ElemType> *tmpPtr = copy.head->next;
        for (; tmpPtr != copy.head; tmpPtr = tmpPtr->next) {
            Insert(Length() + 1, tmpPtr->data);
        }
        curPtr = head;
        curPos = 0;
    }
    return *this;
}


//双向循环链表
template<class ElemType>
class BiLinkList {
protected:
    DblNode<ElemType> *head;
    /* 新添加的数据成员: 记录当前位置/指针以及链表中的元素个数 */
    mutable int curPos;
    mutable DblNode<ElemType> *curPtr;
    int count;


public:
    DblNode<ElemType> *GetElemPtr(int pos) const;

    BiLinkList();

    BiLinkList(const BiLinkList<ElemType> &copy);//拷贝构造函数

    virtual ~BiLinkList();

    int Length() const;//returns the length of linklist

    bool Empty() const;//returns true if the linklist is empty

    void Clear();//clear the linklist

    void Traverse(void(*Visit)(ElemType &)) const;//遍历

    bool GetElem(int pos, ElemType &elem) const;//get the element on pos

    bool SetElem(int pos, const ElemType &key);//set the element on pos to key

    void Insert(int pos, ElemType key);//insert an element with value key before pos

    void Delete(int pos);//delete the element on pos

    BiLinkList<ElemType> &operator=(const BiLinkList<ElemType> &copy);//override operator =
};

template<class ElemType>
DblNode<ElemType> *BiLinkList<ElemType>::GetElemPtr(int pos) const {
    if (pos < 0 || pos > Length()) {
        return nullptr;
    }
    while (curPos < pos) {
        curPtr = curPtr->next;
        curPos++;
    }
    while (curPos > pos) {
        curPtr = curPtr->prev;
        curPos--;
    }
    if (curPtr == head) {
        curPos = 0;
    }
    return curPtr;
}

template<class ElemType>
BiLinkList<ElemType>::BiLinkList() {
    head = new DblNode<ElemType>;
    head->prev = head;
    head->next = head;
    curPtr = head;
    curPos = 0;
    count = 0;
}

template<class ElemType>
bool BiLinkList<ElemType>::GetElem(int pos, ElemType &elem) const {
    if (pos < 1 || pos > Length()) {
        cout << "位置错误" << endl;
        return false;
    } else {
        DblNode<ElemType> *tmpPtr;
        tmpPtr = GetElemPtr(pos);
        elem = tmpPtr->data;
        curPos = pos;
        curPtr = tmpPtr;
        return true;
    }
}

template<class ElemType>
bool BiLinkList<ElemType>::SetElem(int pos, const ElemType &key) {
    if (pos < 1 || pos > Length()) {
        cout << "位置错误" << endl;
        return false;
    } else {
        DblNode<ElemType> *tmpPtr;
        tmpPtr = GetElemPtr(pos);
        tmpPtr->data = key;
        return true;
    }
}

template<class ElemType>
int BiLinkList<ElemType>::Length() const {
    return count;
}

template<class ElemType>
bool BiLinkList<ElemType>::Empty() const {
    return count == 0;
}

template<class ElemType>
void BiLinkList<ElemType>::Insert(int pos, ElemType key) {
    if (pos < 1 || pos > Length() + 1) {
        cout << "位置错误" << endl;
        return;
    } else {
        DblNode<ElemType> *newNode, *nextPtr, *prevPtr;
        prevPtr = GetElemPtr(pos - 1);
        nextPtr = prevPtr->next;
        newNode = new DblNode<ElemType>(key, prevPtr, nextPtr);
        nextPtr->prev = newNode;
        prevPtr->next = newNode;
        curPtr = newNode;
        curPos = pos;
        count++;
    }
}

template<class ElemType>
void BiLinkList<ElemType>::Delete(int pos) {
    if (pos < 1 || pos > Length()) {
        cout << "位置错误" << endl;
        return;
    } else {
        DblNode<ElemType> *tmpPtr, *prevPtr, *nextPtr;
        prevPtr = GetElemPtr(pos - 1);
        tmpPtr = prevPtr->next;
        nextPtr = tmpPtr->next;
        prevPtr->next = nextPtr;
        nextPtr->prev = prevPtr;
        count--;
        delete tmpPtr;
    }
}

template<class ElemType>
void BiLinkList<ElemType>::Traverse(void (*Visit)(ElemType &)) const {
    DblNode<ElemType> *tmpPtr;
    for (tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next) {
        Visit(tmpPtr->data);
    }
}

template<class ElemType>
void BiLinkList<ElemType>::Clear() {
    while (Length() > 0) {
        Delete(1);
    }
}

template<class ElemType>
BiLinkList<ElemType>::BiLinkList(const BiLinkList<ElemType> &copy) {
    head = new DblNode<ElemType>;
    head->prev = head;
    head->next = head;
    curPtr = head;
    curPos = 0;
    count = 0;
    DblNode<ElemType> *tmpPtr = copy.head->next;
    for (; tmpPtr != copy.head; tmpPtr = tmpPtr->next) {
        Insert(Length() + 1, tmpPtr->data);
    }
    curPtr = head;
    curPos = 0;
}

template<class ElemType>
BiLinkList<ElemType>::~BiLinkList() {
    Clear();
    delete head;
}

template<class ElemType>
BiLinkList<ElemType> &BiLinkList<ElemType>::operator=(const BiLinkList<ElemType> &copy) {
    if (&copy != this) {
        Clear();
        head = new DblNode<ElemType>;
        head->prev = head;
        head->next = head;
        curPtr = head;
        curPos = 0;
        count = 0;
        DblNode<ElemType> *tmpPtr = copy.head->next;
        for (; tmpPtr != copy.head; tmpPtr = tmpPtr->next) {
            Insert(Length() + 1, tmpPtr->data);
        }
        curPtr = head;
        curPos = 0;
    }
    return *this;
}

#endif //CLION_MYLIST_H
