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

    bool PushBack(const ElemType &key);

    bool PopFront(ElemType &elem);

    bool PopFront();

    bool Head(ElemType &elem) const;

    void Clear();

    void Traverse(void(*visit)(ElemType &)) const;

    LinkQueue(const LinkQueue<ElemType> &copy);

    LinkQueue<ElemType> &operator=(const LinkQueue<ElemType> &copy);

    ~LinkQueue();

};

template<class ElemType>
LinkQueue<ElemType>::LinkQueue() {
    front = new Node<ElemType>();
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
bool LinkQueue<ElemType>::PushBack(const ElemType &key) {
    auto *newNode = new Node<ElemType>(key, nullptr);
    if (newNode == nullptr) {
        cout << "动态内存已消耗完" << endl;
        return false;
    }
    rear->next = newNode;
    rear = newNode;
    count++;
    return true;
}

template<class ElemType>
bool LinkQueue<ElemType>::PopFront(ElemType &elem) {
    if (Empty()) {
        cout << "队列已空" << endl;
        return false;
    } else {
        Node<ElemType> *tmpPtr = front->next;
        elem = tmpPtr->data;
        front->next = tmpPtr->next;
        if (rear == tmpPtr) {
            rear = front;
        }
        delete tmpPtr;
        count--;
        return true;
    }
}

template<class ElemType>
bool LinkQueue<ElemType>::PopFront() {
    if (Empty()) {
        cout << "队列已空" << endl;
        return false;
    } else {
        Node<ElemType> *tmpPtr = front->next;
        front->next = tmpPtr->next;
        if (rear == tmpPtr) {
            rear = front;
        }
        delete tmpPtr;
        count--;
        return true;
    }
}

template<class ElemType>
bool LinkQueue<ElemType>::Head(ElemType &elem) const {
    if (Empty()) {
        cout << "队列已空" << endl;
        return false;
    } else {
        elem = front->next->data;
        return true;
    }
}

template<class ElemType>
void LinkQueue<ElemType>::Traverse(void (*visit)(ElemType &)) const {
    for (Node<ElemType> *tmpPtr = front->next; tmpPtr != nullptr; tmpPtr = tmpPtr->next) {
        visit(tmpPtr->data);
    }
}

template<class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> &copy) {
    front = new Node<ElemType>();
    rear = front;
    count = 0;
    Node<ElemType> *tmpPtr = copy.front->next;
    for (; tmpPtr != nullptr; tmpPtr = tmpPtr->next) {
        PushBack(tmpPtr->data);
    }
}

template<class ElemType>
LinkQueue<ElemType> &LinkQueue<ElemType>::operator=(const LinkQueue<ElemType> &copy) {
    if (&copy != this) {
        Clear();
        if (front == nullptr) {
            delete front;
            front = nullptr;
        }
        front = new Node<ElemType>();
        rear = front;
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
    int count;
    ElemType *q;
public:
    explicit SqQueue(int size = 20);

    int Length() const;

    bool Empty() const;

    bool Full() const;

    void Clear();

    void Traverse(void(*visit)(ElemType &)) const;

    bool PushBack(const ElemType &key);

    bool PopFront(ElemType &elem);

    bool PopFront();

    bool Head(ElemType &elem) const;

    SqQueue(const SqQueue<ElemType> &copy);

    SqQueue<ElemType> &operator=(const SqQueue<ElemType> &copy);

    ~SqQueue();
};

template<class ElemType>
SqQueue<ElemType>::SqQueue(int size) {
    maxSize = size;
    front = rear = 0;
    q = new ElemType[maxSize];
}

template<class ElemType>
int SqQueue<ElemType>::Length() const {
    // 空出一个位置用于判满
    return (rear - front + maxSize) % maxSize;
}

template<class ElemType>
bool SqQueue<ElemType>::Empty() const {
    return front == rear;
}

template<class ElemType>
bool SqQueue<ElemType>::Full() const {
    return Length() == maxSize - 1;
}

template<class ElemType>
bool SqQueue<ElemType>::PushBack(const ElemType &key) {
    if (Full()) {
        cout << "队列已满" << endl;
        return false;
    } else {
        q[rear] = key;
        rear = (rear + 1) % maxSize;
        return true;
    }
}

template<class ElemType>
bool SqQueue<ElemType>::PopFront(ElemType &elem) {
    if (Empty()) {
        cout << "队列已空" << endl;
        return false;
    } else {
        elem = q[front];
        front = (front + 1) % maxSize;
        return true;
    }
}

template<class ElemType>
bool SqQueue<ElemType>::PopFront() {
    if (Empty()) {
        cout << "队列已空" << endl;
        return false;
    } else {
        front = (front + 1) % maxSize;
        return true;
    }
}

template<class ElemType>
bool SqQueue<ElemType>::Head(ElemType &elem) const {
    if (Empty()) {
        cout << "队列已空" << endl;
        return false;
    } else {
        elem = q[front];
        return true;
    }
}

template<class ElemType>
void SqQueue<ElemType>::Clear() {
    while (!Empty()) {
        PopFront();
    }
}

template<class ElemType>
void SqQueue<ElemType>::Traverse(void (*visit)(ElemType &)) const {
    for (int i = front; i != rear; i = (i + 1) % maxSize) {
        visit(q[i]);
    }
}

template<class ElemType>
SqQueue<ElemType>::SqQueue(const SqQueue<ElemType> &copy) {
    front = 0;
    rear = 0;
    maxSize = copy.maxSize;
    q = new ElemType[maxSize];
    for (int i = copy.front; i != copy.rear; i = (i + 1) % maxSize) {
        PushBack(copy.q[i]);
    }
}

template<class ElemType>
SqQueue<ElemType> &SqQueue<ElemType>::operator=(const SqQueue<ElemType> &copy) {
    if (&copy != this) {
        if (q != nullptr) {
            delete q;
            q = nullptr;
        }
        front = 0;
        rear = 0;
        maxSize = copy.maxSize;
        q = new ElemType[maxSize];
        for (int i = copy.front; i != copy.rear; i = (i + 1) % maxSize) {
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
