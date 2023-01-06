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
    int count;//˳����е�Ԫ�ظ���
    int maxSize;//˳������Ԫ�ظ���
    ElemType *sqList;

    //��������
    bool Full() const;//�ж����Ա��Ƿ�����
public:
    explicit SqList(int size = DEFAULT_N);//���캯��   explicit�ؼ��� --- ������ʽ����ת��
    SqList(const SqList<ElemType> &copy);//�������캯��
    virtual ~SqList();//��������
    int Length() const;//����˳�����
    bool Empty() const;//�ж�˳����Ƿ�Ϊ��
    void Clear();//���˳���
    void Traverse(void(*Visit)(ElemType &));

    ElemType GetElem(int pos) const;//����ָ��λ�õ�Ԫ��
    void SetElem(int pos, const ElemType &key);//����ָ��λ�õ�Ԫ��
    void Delete(int pos);//ɾ��ָ��λ�õ�Ԫ��
    void Insert(int pos, const ElemType &key);//��ָ��λ�ò���ָ����ֵ
    SqList<ElemType> &operator=(const SqList<ElemType> &copy);//���ظ�ֵ�����
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
void SqList<ElemType>::Traverse(void (*Visit)(ElemType &)) {
    for (int i = 1; i <= Length(); i++) {
        Visit(sqList[i - 1]);
    }
}

template<class ElemType>
ElemType SqList<ElemType>::GetElem(int pos) const {
    if (pos < 1 || pos > Length()) {
        cout << "λ�ô���\n";
        return 0;
    } else {
        return sqList[pos - 1];
    }
}

template<class ElemType>
void SqList<ElemType>::SetElem(int pos, const ElemType &key) {
    if (pos < 1 || pos > Length()) {
        cout << "λ�ô���\n";
        return;
    } else {
        sqList[pos - 1] = key;
    }
}

template<class ElemType>
void SqList<ElemType>::Delete(int pos) {
    if (Empty()) {
        cout << "˳����Ѿ�Ϊ��\n";
        return;
    } else if (pos < 1 || pos > count) {
        cout << "λ�ô���\n";
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
        cout << "˳�������\n";
        return;
    } else if (pos < 1 || pos > Length() + 1) {
        cout << "λ�ô���\n";
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
        for (int i = 0; i < copy.count; i++) {
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
    for (int i = 0; i < copy.count; i++) {
        sqList[i] = copy.sqList[i];
    }
}

template<class ElemType>
SqList<ElemType>::~SqList() {
    delete[] sqList;
}


//��������
template<class ElemType>
class SimpleLinkList {
protected:
    Node<ElemType> *head;

    //��������
    Node<ElemType> *GetElemPtr(int pos) const;//���ص�pos������ָ��

public:
    SimpleLinkList();

    virtual ~SimpleLinkList();

    int Length() const;//����������

    bool Empty() const;//�п�

    void Clear();//�������

    void Traverse(void(*Visit)(ElemType &));//��������Ԫ�ز�ִ��Visit����

    ElemType GetElem(int pos) const;//��ȡpos�ϵ�Ԫ��

    void SetElem(int pos, ElemType key);//�ı�pos�ϵ�Ԫ��

    void Delete(int pos);//ɾ��pos�ϵ�Ԫ��

    void Insert(int pos, ElemType key);//��pos����һ��Ԫ��

    void reverse();//��ת����

    SimpleLinkList(const SimpleLinkList<ElemType> &copy);//�������캯��

    SimpleLinkList<ElemType> &operator=(const SimpleLinkList<ElemType> &copy);//���ظ�ֵ�����
};

template<class ElemType>
Node<ElemType> *SimpleLinkList<ElemType>::GetElemPtr(int pos) const {
    Node<ElemType> *node = head;
    int curPos = 0;
    while (node != nullptr && curPos != pos) {
        node = node->next;
        curPos++;
    }
    if (node != nullptr && curPos == pos) {
        //���ҳɹ�
        return node;
    } else {
        //����ʧ��
        return nullptr;
    }
}

template<class ElemType>
SimpleLinkList<ElemType>::SimpleLinkList() {
    head = new Node<ElemType>(0, nullptr);
}

template<class ElemType>
int SimpleLinkList<ElemType>::Length() const {
    int count = 0;
    Node<ElemType> *tmpPtr = head->next;
    while (tmpPtr != nullptr) {
        count++;
        tmpPtr = tmpPtr->next;
    }
    return count;
}

template<class ElemType>
bool SimpleLinkList<ElemType>::Empty() const {
    return head->next == nullptr;
}

template<class ElemType>
void SimpleLinkList<ElemType>::Clear() {
    while (Length() > 0) {
        Delete(1);//��ͣɾ����һ����㣬ֱ������Ϊ��
    }
}

template<class ElemType>
void SimpleLinkList<ElemType>::Traverse(void(*Visit)(ElemType &)) {
    for (int i = 1; i <= Length(); i++) {
        Node<ElemType> *tmpPtr = GetElemPtr(i);
        Visit(tmpPtr->data);
    }
}

template<class ElemType>
ElemType SimpleLinkList<ElemType>::GetElem(int pos) const {
    if (pos < 1 || pos > Length()) {
        cout << "λ�ô���" << endl;
        return 0;
    } else {
        Node<ElemType> *tmpPtr = GetElemPtr(pos);
        return tmpPtr->data;
    }
}

template<class ElemType>
void SimpleLinkList<ElemType>::SetElem(int pos, ElemType key) {
    if (pos < 1 || pos > Length()) {
        cout << "λ�ô���" << endl;
        return;
    } else {
        Node<ElemType> *tmpPtr = GetElemPtr(pos);
        tmpPtr->data = key;
    }

}

template<class ElemType>
void SimpleLinkList<ElemType>::Insert(int pos, ElemType key) {
    if (pos < 1 || pos > Length() + 1) {
        cout << "λ�ô���" << endl;
        return;
    } else {
        Node<ElemType> *newNode;
        Node<ElemType> *tmpPtr;
        tmpPtr = GetElemPtr(pos - 1);
        newNode = new Node<ElemType>(key, tmpPtr->next);
        tmpPtr->next = newNode;
    }
}

template<class ElemType>
void SimpleLinkList<ElemType>::Delete(int pos) {
    if (pos < 1 || pos > Length()) {
        cout << "λ�ô���" << endl;
        return;
    } else {
        Node<ElemType> *tmpPtr = GetElemPtr(pos - 1);
        Node<ElemType> *nextPtr = tmpPtr->next;
        tmpPtr->next = nextPtr->next;
        delete nextPtr;
    }
}

template<class ElemType>
void SimpleLinkList<ElemType>::reverse() {
    Node<ElemType> *tmpPtr = nullptr, *nextPtr = nullptr, *curPtr;
    curPtr = head->next;
    while (curPtr != nullptr) {
        tmpPtr = curPtr->next;
        curPtr->next = nextPtr;
        nextPtr = curPtr;
        curPtr = tmpPtr;
    }
    head->next = nextPtr;
}

template<class ElemType>
SimpleLinkList<ElemType>::SimpleLinkList(const SimpleLinkList<ElemType> &copy) {
    head = new Node<ElemType>(0, nullptr);
    Node<ElemType> *tmpPtr = copy.head->next;
    for (; tmpPtr != nullptr; tmpPtr = tmpPtr->next) {
        Insert(Length() + 1, tmpPtr->data);
    }
}

template<class ElemType>
SimpleLinkList<ElemType>::~SimpleLinkList() {
    delete head;
}

template<class ElemType>
SimpleLinkList<ElemType> &SimpleLinkList<ElemType>::operator=(const SimpleLinkList<ElemType> &copy) {
    if (&copy != this) {
        Clear();
        head = new Node<ElemType>(0, nullptr);
        Node<ElemType> *tmpPtr = copy.head->next;
        for (; tmpPtr != nullptr; tmpPtr = tmpPtr->next) {
            Insert(Length() + 1, tmpPtr->data);
        }
    }
    return *this;
}


//ѭ������
template<class ElemType>
class CircleLinkList {
protected:
    Node<ElemType> *head;

    //��������
    Node<ElemType> *GetElemPtr(int pos) const;//���ص�pos������ָ��

public:
    CircleLinkList();

    virtual ~CircleLinkList();

    int Length() const;//����������

    bool Empty() const;//�п�

    void Clear();// clear all elements in the list

    void Traverse(void(*Visit)(ElemType &));//traverse the linklist by applying Visit function to all elements

    ElemType GetElem(int pos) const;//get the element on pos

    void SetElem(int pos, ElemType key);//set the element on pos to key

    void Delete(int pos);//delete the element on pos

    void Insert(int pos, ElemType key);//insert an element with value key before pos

    CircleLinkList(const CircleLinkList<ElemType> &copy);//�������캯��

    CircleLinkList<ElemType> &operator=(const CircleLinkList<ElemType> &copy);//���ظ�ֵ�����
};

template<class ElemType>
Node<ElemType> *CircleLinkList<ElemType>::GetElemPtr(int pos) const {
    /*============================*/
    if (pos == 0) {
        return head;
    }
    Node<ElemType> *tmpPtr = head->next;
    int curPos = 1;
    /*============================*/
    while (tmpPtr != head && curPos != pos) {
        tmpPtr = tmpPtr->next;
        curPos++;
    }
    if (tmpPtr != head && curPos == pos) {
        //���ҳɹ�
        return tmpPtr;
    } else {
        //����ʧ��
        return nullptr;
    }
}

template<class ElemType>
CircleLinkList<ElemType>::CircleLinkList() {
    head = new Node<ElemType>;
    /*============================*/
    head->next = head;
    /*============================*/
}

template<class ElemType>
int CircleLinkList<ElemType>::Length() const {
    int count = 0;
    Node<ElemType> *tmpPtr = head->next;
    /*============================*/
    while (tmpPtr != head) {
        /*============================*/
        tmpPtr = tmpPtr->next;
        count++;
    }
    return count;
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
        Delete(1);//��ͣɾ����һ����㣬ֱ������Ϊ��
    }
}

template<class ElemType>
void CircleLinkList<ElemType>::Traverse(void(*Visit)(ElemType &)) {
    for (int i = 1; i <= Length(); i++) {
        Node<ElemType> *tmpPtr = GetElemPtr(i);
        Visit(tmpPtr->data);
    }
}

template<class ElemType>
ElemType CircleLinkList<ElemType>::GetElem(int pos) const {
    if (pos < 1 || pos > Length()) {
        cout << "λ�ô���" << endl;
        return 0;
    } else {
        Node<ElemType> *tmpPtr = GetElemPtr(pos);
        return tmpPtr->data;
    }
}

template<class ElemType>
void CircleLinkList<ElemType>::SetElem(int pos, ElemType key) {
    if (pos < 1 || pos > Length()) {
        cout << "λ�ô���" << endl;
        return;
    } else {
        Node<ElemType> *tmpPtr = GetElemPtr(pos);
        tmpPtr->data = key;
    }
}

template<class ElemType>
void CircleLinkList<ElemType>::Insert(int pos, ElemType key) {
    if (pos < 1 || pos > Length() + 1) {
        cout << "λ�ô���" << endl;
        return;
    } else {
        Node<ElemType> *newNode;
        Node<ElemType> *tmpPtr;
        tmpPtr = GetElemPtr(pos - 1);
        newNode = new Node<ElemType>(key, tmpPtr->next);
        tmpPtr->next = newNode;
    }
}

template<class ElemType>
void CircleLinkList<ElemType>::Delete(int pos) {
    if (pos < 1 || pos > Length()) {
        cout << "λ�ô���" << endl;
        return;
    } else {
        Node<ElemType> *tmpPtr = GetElemPtr(pos - 1);
        Node<ElemType> *nextPtr = tmpPtr->next;//node to be deleted
        tmpPtr->next = nextPtr->next;
        delete nextPtr;
    }
}

template<class ElemType>
CircleLinkList<ElemType>::CircleLinkList(const CircleLinkList<ElemType> &copy) {
    head = new Node<ElemType>;
    head->next = head;
    Node<ElemType> *tmpPtr = copy.head->next;
    for (; tmpPtr != copy.head; tmpPtr = tmpPtr->next) {
        Insert(Length() + 1, tmpPtr->data);
    }
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
        Node<ElemType> *tmpPtr = copy.head->next;
        for (; tmpPtr != copy.head; tmpPtr = tmpPtr->next) {
            Insert(Length() + 1, tmpPtr->data);
        }
    }
    return *this;
}


//˫��ѭ������
template<class ElemType>
class BiLinkList {
protected:
    DblNode<ElemType> *head;
    /* ����ӵ����ݳ�Ա��¼��ǰλ��/ָ���Լ������е�Ԫ�ظ��� */
    mutable int curPos;
    mutable DblNode<ElemType> *curPtr;
    int count;


    DblNode<ElemType> *GetElemPtr(int pos) const;

public:
    BiLinkList();

    BiLinkList(const BiLinkList<ElemType> &copy);//�������캯��

    virtual ~BiLinkList();

    int Length() const;//returns the length of linklist

    bool Empty() const;//returns true if the linklist is empty

    void Clear();//clear the linklist

    void Traverse(void(*Visit)(ElemType &)) const;//����

    ElemType GetElem(int pos) const;//get the element on pos

    void SetElem(int pos, ElemType key);//set the element on pos to key

    void Insert(int pos, ElemType key);//insert an element with value key before pos

    void Delete(int pos);//delete the element on pos

    BiLinkList<ElemType> &operator=(const BiLinkList<ElemType> &copy);//override operator =
};

template<class ElemType>
DblNode<ElemType> *BiLinkList<ElemType>::GetElemPtr(int pos) const {
    while (curPos < pos) {
        curPtr = curPtr->next;
        curPos++;
    }
    while (curPos > pos) {
        curPtr = curPtr->prev;
        curPos--;
    }
//    if (curPtr != head && curPos == pos) {
//        return curPtr;
//    } else if (curPtr == head) {
//        curPos = 0;
//        return head;
//    }
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
ElemType BiLinkList<ElemType>::GetElem(int pos) const {
    if (pos < 1 || pos > Length()) {
        cout << "λ�ô���" << endl;
        exit(1);
    } else {
        DblNode<ElemType> *tmpPtr;
        tmpPtr = GetElemPtr(pos);
        return tmpPtr->data;
    }
}

template<class ElemType>
void BiLinkList<ElemType>::SetElem(int pos, ElemType key) {
    if (pos < 1 || pos > Length()) {
        cout << "λ�ô���" << endl;
        return;
    } else {
        DblNode<ElemType> *tmpPtr;
        tmpPtr = GetElemPtr(pos);
        tmpPtr->data = key;
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
        cout << "λ�ô���" << endl;
        return;
    } else {
        DblNode<ElemType> *newNode, *nextPtr, *prevPtr;
        nextPtr = GetElemPtr(pos);
        prevPtr = nextPtr->prev;
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
        cout << "λ�ô���" << endl;
        return;
    } else {
        DblNode<ElemType> *tmpPtr, *prevPtr, *nextPtr;
        tmpPtr = GetElemPtr(pos);
        prevPtr = tmpPtr->prev;
        nextPtr = tmpPtr->next;
        prevPtr->next = nextPtr;
        nextPtr->prev = prevPtr;
        if (pos == Length()) {
            curPos = 0;
            curPtr = head;
        } else {
            curPtr = nextPtr;
            curPos = pos;
        }
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
