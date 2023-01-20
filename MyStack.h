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

    void Traverse(void(*visit)(ElemType &)) const;

    void Push(const ElemType &key);

    bool Pop(ElemType &elem);

    bool Pop();

    bool Top(ElemType &elem) const;

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
void SqStack<ElemType>::Traverse(void (*visit)(ElemType &)) const {
    for (int i = 0; i < count; i++) {
        visit(stack[i]);
    }
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
bool SqStack<ElemType>::Pop() {
    if (Empty()) {
        cout << "栈已空" << endl;
        return false;
    } else {
        count--;
    }
}

template<class ElemType>
bool SqStack<ElemType>::Pop(ElemType &elem) {
    if (Empty()) {
        cout << "栈已空" << endl;
        return false;
    } else {
        elem = stack[--count];
        return true;
    }
}

template<class ElemType>
bool SqStack<ElemType>::Top(ElemType &elem) const {
    if (!Empty()) {
        elem = stack[count - 1];
        return true;
    } else {
        cout << "栈已空" << endl;
        return false;
    }
}

template<class ElemType>
void SqStack<ElemType>::Clear() {
    // 逻辑上清空，更简单，节省空间、时间
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
        if (stack != nullptr) {
            delete stack;
            stack = nullptr;
        }
        this->count = copy.count;
        this->maxSize = copy.maxSize;
        stack = new ElemType[maxSize];
        for (int i = 0; i < copy.count; i++) {
            stack[i] = copy.stack[i];
        }
    }
    return *this;
}

template<class ElemType>
SqStack<ElemType>::~SqStack() {
    if (stack != nullptr) {
        delete[] stack;
        stack = nullptr;
    }
}

//链式栈
template<class ElemType>
struct StackNode {
    ElemType data{};
    StackNode *next;

    StackNode();

    StackNode(ElemType d, StackNode *n);
};

template<class ElemType>
StackNode<ElemType>::StackNode() {
    next = nullptr;
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

    void Traverse(void(*visit)(ElemType &));

    void Push(const ElemType &key);

    bool Pop();

    bool Pop(ElemType &elem);

    bool Top(ElemType &elem) const;

    LinkStack<ElemType> &operator=(const LinkStack<ElemType> &copy);

    virtual ~LinkStack();
};

template<class ElemType>
LinkStack<ElemType>::LinkStack() {
    top = nullptr;
    count = 0;
}

template<class ElemType>
int LinkStack<ElemType>::Length() const {
    return count;
}

template<class ElemType>
bool LinkStack<ElemType>::Empty() const {
    return top == nullptr;
}

template<class ElemType>
void LinkStack<ElemType>::Clear() {
    while (!Empty()) {
        Pop();
    }
}

template<class ElemType>
void LinkStack<ElemType>::Traverse(void (*visit)(ElemType &)) {
    StackNode<ElemType> *tmpPtr;
    LinkStack<ElemType> tempS;
    ElemType elem;
    for (tmpPtr = top; tmpPtr != nullptr; tmpPtr = tmpPtr->next) {
        // 将栈中所有元素放入一个新的栈中，顺序为栈底->栈顶
        visit(tmpPtr->data);
    }
}

template<class ElemType>
void LinkStack<ElemType>::Push(const ElemType &key) {
    auto *newNode = new StackNode<ElemType>(key, top);
    if (newNode == nullptr) {
        cout << "动态内存耗尽" << endl;
    } else {
        top = newNode;
        count++;
    }
}

template<class ElemType>
bool LinkStack<ElemType>::Pop(ElemType &elem) {
    if (Empty()) {
        cout << "栈已空" << endl;
        return false;
    } else {
        StackNode<ElemType> *tmpPtr;
        tmpPtr = top;
        elem = tmpPtr->data;
        top = top->next;
        count--;
        delete tmpPtr;
        return true;
    }
}

template<class ElemType>
bool LinkStack<ElemType>::Pop() {
    if (Empty()) {
        cout << "栈已空" << endl;
        return false;
    } else {
        StackNode<ElemType> *tmpPtr;
        tmpPtr = top;
        top = top->next;
        count--;
        delete tmpPtr;
        return true;
    }
}

template<class ElemType>
bool LinkStack<ElemType>::Top(ElemType &elem) const {
    if (Empty()) {
        cout << "栈已空" << endl;
        return false;
    } else {
        elem = top->data;
        return true;
    }
}

template<class ElemType>
LinkStack<ElemType>::LinkStack(const LinkStack<ElemType> &copy) {
    if (copy.Empty()) {
        //copy is empty stack
        top = nullptr;
    } else {
        //copy isn't empty stack
        top = new StackNode<ElemType>(copy.top->data, nullptr);
        StackNode<ElemType> *buttomPtr = top;//当前栈底
        for (StackNode<ElemType> *tmpPtr = copy.top->next; tmpPtr != nullptr; tmpPtr = tmpPtr->next) {
            buttomPtr->next = new StackNode<ElemType>(tmpPtr->data, nullptr);
            buttomPtr = buttomPtr->next;
        }

    }
}

template<class ElemType>
LinkStack<ElemType> &LinkStack<ElemType>::operator=(const LinkStack<ElemType> &copy) {
    if (&copy != this) {
        if (copy.Empty()) {
//        copy is empty stack
            top = nullptr;
        } else {
//        copy isn't empty stack
            if (top != nullptr) {
                delete top;
                top = nullptr;
            }
            top = new StackNode<ElemType>(copy.top->data, nullptr);
            StackNode<ElemType> *buttomPtr = top;//当前栈底
            for (StackNode<ElemType> *tmpPtr = copy.top->next; tmpPtr != nullptr; tmpPtr = tmpPtr->next) {
                buttomPtr->next = new StackNode<ElemType>(tmpPtr->data, nullptr);
                buttomPtr = buttomPtr->next;
            }
        }
    }
    return *this;
}

template<class ElemType>
LinkStack<ElemType>::~LinkStack() {
    if (top != nullptr) {
        delete top;
        top = nullptr;
    }
}

#endif //CLION_MYSTACK_H
