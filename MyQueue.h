//
// Created by HP on 2022/9/17.
//

#ifndef CLION_MYQUEUE_H
#define CLION_MYQUEUE_H

#include<iostream>
#include"Node.h"

using namespace std;

//链式队列
template<class ElemType>
class LinkQueue {
protected:
    //分别表示对头和队尾指针
    Node<ElemType> *front, *rear;
    //队内元素个数
    int count;
public:
    LinkQueue();

    int Length() const;

    bool Empty() const;

    void PushBack(ElemType key);

    ElemType PopFront();

    ElemType GetHead() const;

    void Clear();

    LinkQueue(const LinkQueue<ElemType> &copy);

    LinkQueue<ElemType> &operator=(const LinkQueue<ElemType> &copy);

    ~LinkQueue();

};

template<class ElemType>
LinkQueue<ElemType>::LinkQueue() {
    front = new Node<ElemType>(0, NULL);
    rear = front;
    count = 0;
}

template<class ElemType>
int LinkQueue<ElemType>::Length() const {
    return count;
}

template<class ElemType>
bool LinkQueue<ElemType>::Empty() const {
    return front == rear;
}

template<class ElemType>
void LinkQueue<ElemType>::Clear() {
    while (!Empty()) {
        PopFront();
    }
}

template<class ElemType>
void LinkQueue<ElemType>::PushBack(ElemType key) {
    auto *newNode = new Node<ElemType>(key, NULL);
    if (newNode == NULL) {
        cout << "动态内存已消耗完" << endl;
        exit(1);
    }
    rear->next = newNode;
    rear = newNode;
    count++;
}

template<class ElemType>
ElemType LinkQueue<ElemType>::PopFront() {
    if (Empty()) {
        cout << "队列已空" << endl;
        exit(1);
    } else {
        Node<ElemType> *tmpPtr = front->next;
        front->next = tmpPtr->next;
        ElemType elem = tmpPtr->data;
        if (rear == tmpPtr) {
            rear = front;
        }
        delete tmpPtr;
        count--;
        return elem;
    }
}

template<class ElemType>
ElemType LinkQueue<ElemType>::GetHead() const {
    if (Empty()) {
        cout << "队列已空" << endl;
        exit(1);
    } else {
        Node<ElemType> *tmpPtr = front->next;
        return tmpPtr->data;
    }
}

template<class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> &copy) {
    front = new Node<ElemType>(0, NULL);
    rear = front;
    count = 0;
    Node<ElemType> *tmpPtr = copy.front->next;
    for (; tmpPtr != NULL; tmpPtr = tmpPtr->next) {
        PushBack(tmpPtr->data);
    }
}

template<class ElemType>
LinkQueue<ElemType> &LinkQueue<ElemType>::operator=(const LinkQueue<ElemType> &copy) {
    if (&copy != this) {
        Clear();
        Node<ElemType> *tmpPtr = copy.front->next;
        for (int i = 1; i <= copy.Length(); i++) {
            PushBack(tmpPtr->data);
            tmpPtr = tmpPtr->next;
        }
    }
    return *this;
}

template<class ElemType>
LinkQueue<ElemType>::~LinkQueue() {
    Clear();
    delete front;
}


//循环队列
template<class ElemType>
class SqQueue {
protected:
    int front, rear;
    int maxSize;
    ElemType *q;
public:
    explicit SqQueue(int size = 20);

    int Length() const;

    bool Empty() const;

    bool Full() const;

    void Clear();

    void PushBack(ElemType key);

    ElemType PopFront();

    ElemType GetHead() const;

    SqQueue(const SqQueue<ElemType> &copy);

    SqQueue<ElemType> &operator=(const SqQueue<ElemType> &copy);

    ~SqQueue();
};

template<class ElemType>
SqQueue<ElemType>::SqQueue(int size) {
    maxSize = size;
    front = 0;
    rear = 0;
    q = new ElemType[maxSize];
}

template<class ElemType>
int SqQueue<ElemType>::Length() const {
    return (rear - front + maxSize) % maxSize;
}

template<class ElemType>
bool SqQueue<ElemType>::Empty() const {
    return rear == front;
}

template<class ElemType>
bool SqQueue<ElemType>::Full() const {
    return Length() == maxSize - 1;
}

template<class ElemType>
void SqQueue<ElemType>::PushBack(ElemType key) {
    if (Full()) {
        cout << "队列已满" << endl;
        exit(1);
    } else {
        q[rear] = key;
        rear = (rear + 1) % maxSize;
    }
}

template<class ElemType>
ElemType SqQueue<ElemType>::PopFront() {
    if (Empty()) {
        cout << "队列已空" << endl;
        exit(1);
    } else {
        ElemType elem = q[front];
        front = (front + 1) % maxSize;
        return elem;
    }
}

template<class ElemType>
ElemType SqQueue<ElemType>::GetHead() const {
    if (Empty()) {
        cout << "队列已空" << endl;
        exit(1);
    } else {
        ElemType elem = q[front];
        return elem;
    }
}

template<class ElemType>
void SqQueue<ElemType>::Clear() {
    while (!Empty()) {
        PopFront();
    }
}

template<class ElemType>
SqQueue<ElemType>::SqQueue(const SqQueue<ElemType> &copy) {
    front = 0;
    rear = 0;
    maxSize = copy.maxSize;
    q = new ElemType[maxSize];
    for (int i = copy.front; i != copy.rear; i = (i + 1) % copy.maxSize) {
        PushBack(copy.q[i]);
    }
}

template<class ElemType>
SqQueue<ElemType> &SqQueue<ElemType>::operator=(const SqQueue<ElemType> &copy) {
    if (&copy != this) {
        Clear();
        front = 0;
        rear = 0;
        maxSize = copy.maxSize;
        for (int i = copy.front; i != copy.rear; i = (i + 1) % copy.maxSize) {
            PushBack(copy.q[i]);
        }
    }
    return *this;
}

template<class ElemType>
SqQueue<ElemType>::~SqQueue() {
    delete q;
}

#endif //CLION_MYQUEUE_H
