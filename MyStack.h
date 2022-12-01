//
// Created by HP on 2022/9/17.
//

#ifndef CLION_MYSTACK_H
#define CLION_MYSTACK_H

#include<iostream>

using namespace std;

//顺序栈
template<class ElemType>
class SqStack {
protected:
    int count{};
    int maxSize{};
    ElemType *stack;

    bool Full() const;

public:
    explicit SqStack(int size = 20);

    SqStack(const SqStack<ElemType> &copy);

    int Length() const;

    bool Empty() const;

    void Clear();

    void Push(const ElemType &key);

    ElemType Pop();

    SqStack<ElemType> &operator=(const SqStack<ElemType> &copy);

    ~SqStack();

};

template<class ElemType>
bool SqStack<ElemType>::Full() const {
    return count == maxSize;
}

template<class ElemType>
SqStack<ElemType>::SqStack(int size) {
    count = 0;
    maxSize = size;
    stack = new ElemType[size];
}

template<class ElemType>
int SqStack<ElemType>::Length() const {
    return count;
}

template<class ElemType>
bool SqStack<ElemType>::Empty() const {
    return count == 0;
}

template<class ElemType>
void SqStack<ElemType>::Push(const ElemType &key) {
    if (Full()) {
        cout << "栈已满" << endl;
        return;
    } else {
        stack[count++] = key;
    }
}

template<class ElemType>
ElemType SqStack<ElemType>::Pop() {
    if (Empty()) {
        cout << "栈已空" << endl;
        return 0;
    } else {
        ElemType elem = stack[--count];
        return elem;
    }
}

template<class ElemType>
void SqStack<ElemType>::Clear() {
    count = 0;
}

template<class ElemType>
SqStack<ElemType>::SqStack(const SqStack<ElemType> &copy) {
    this->count = copy.count;
    this->maxSize = copy.maxSize;
    stack = new ElemType[maxSize];
    for (int i = 0; i < copy.count; i++) {
        stack[i] = copy.stack[i];
    }
}

template<class ElemType>
SqStack<ElemType> &SqStack<ElemType>::operator=(const SqStack<ElemType> &copy) {
    if (&copy != this) {
        this->count = copy.count;
        this->maxSize = copy.maxSize;
        for (int i = 0; i < copy.count; i++) {
            stack[i] = copy.stack[i];
        }
    }
    return *this;
}

template<class ElemType>
SqStack<ElemType>::~SqStack() {
    if (stack != NULL) {
        delete[] stack;
        stack = NULL;
    }
}


//链式栈
template<class ElemType>
struct StackNode {
    ElemType data;
    StackNode *next;

    StackNode();

    StackNode(ElemType d, StackNode *n);
};

template<class ElemType>
StackNode<ElemType>::StackNode() {
    data = 0;
    next = NULL;
}

template<class ElemType>
StackNode<ElemType>::StackNode(ElemType d, StackNode<ElemType> *n) {
    this->data = d;
    next = n;
}

template<class ElemType>
class LinkStack {
protected:
    StackNode<ElemType> *top;
    int count{};

public:
    LinkStack();

    LinkStack(const LinkStack<ElemType> &copy);

    int Length() const;

    bool Empty() const;

    void Clear();

    void Push(const ElemType &key);

    ElemType Pop();

    ElemType GetHead();

    LinkStack<ElemType> &operator=(const LinkStack<ElemType> &copy);

    virtual ~LinkStack();
};

template<class ElemType>
LinkStack<ElemType>::LinkStack() {
    top = NULL;
    count = 0;
}

template<class ElemType>
int LinkStack<ElemType>::Length() const {
    return count;
}

template<class ElemType>
bool LinkStack<ElemType>::Empty() const {
    return top == NULL;
}

template<class ElemType>
void LinkStack<ElemType>::Clear() {
    while (!Empty()) {
        Pop();
    }
}

template<class ElemType>
void LinkStack<ElemType>::Push(const ElemType &key) {
    auto *newNode = new StackNode<ElemType>(key, top);
    if (newNode == NULL) {
        cout << "动态内存耗尽" << endl;
    } else {
        top = newNode;
        count++;
    }
}

template<class ElemType>
ElemType LinkStack<ElemType>::Pop() {
    if (Empty()) {
        cout << "栈已空" << endl;
        return 0;
    } else {
        StackNode<ElemType> *tmpPtr;
        tmpPtr = top;
        ElemType e = tmpPtr->data;
        top = top->next;
        count--;
        delete tmpPtr;
        return e;
    }
}

template<class ElemType>
ElemType LinkStack<ElemType>::GetHead() {
    if (Empty()) {
        cout << "栈已空" << endl;
        return 0;
    } else {
        return top->data;
    }
}

template<class ElemType>
LinkStack<ElemType>::LinkStack(const LinkStack<ElemType> &copy) {
    if (copy.Empty()) {
        //copy is empty stack
        top = NULL;
    } else {
        //copy isn't empty stack
        top = new StackNode<ElemType>(copy.top->data, NULL);
        StackNode<ElemType> *buttomPtr = top;//当前栈底
        for (StackNode<ElemType> *tmpPtr = copy.top->next; tmpPtr != NULL; tmpPtr = tmpPtr->next) {
            buttomPtr->next = new StackNode<ElemType>(tmpPtr->data, NULL);
            buttomPtr = buttomPtr->next;
        }

    }
}

template<class ElemType>
LinkStack<ElemType> &LinkStack<ElemType>::operator=(const LinkStack<ElemType> &copy) {
    if (&copy != this) {
        if (copy.Empty()) {
//        copy is empty stack
            top = NULL;
        } else {
//        copy isn't empty stack
            top = new StackNode<ElemType>(copy.top->data, NULL);
            StackNode<ElemType> *buttomPtr = top;//当前栈底
            for (StackNode<ElemType> *tmpPtr = copy.top->next; tmpPtr != NULL; tmpPtr = tmpPtr->next) {
                buttomPtr->next = new StackNode<ElemType>(tmpPtr->data, NULL);
                buttomPtr = buttomPtr->next;
            }

        }
    }
    return *this;
}

template<class ElemType>
LinkStack<ElemType>::~LinkStack() {
    if (top != NULL) {
        delete top;
        top = NULL;
    }
}

#endif //CLION_MYSTACK_H
