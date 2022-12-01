//
// Created by HP on 2022/9/13.
//


#include<iostream>
#include<cstring>

using namespace std;

//Ë³ÐòÕ»
template<class ElemType>
class SqStack {
protected:
    int count;
    int maxSize;
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
        cout << "Õ»ÒÑÂú" << endl;
        return;
    } else {
        stack[count++] = key;
    }
}

template<class ElemType>
ElemType SqStack<ElemType>::Pop() {
    if (Empty()) {
        cout << "Õ»ÒÑ¿Õ" << endl;
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


//Á´Ê½Õ»
template<class ElemType>
struct Node {
    ElemType data;
    Node *next;

    Node();

    Node(ElemType d, Node *n);
};

template<class ElemType>
Node<ElemType>::Node() {
    data = 0;
    next = NULL;
}

template<class ElemType>
Node<ElemType>::Node(ElemType d, Node<ElemType> *n) {
    this->data = d;
    next = n;
}

template<class ElemType>
class LinkStack {
protected:
    Node<ElemType> *top;
    int count;

public:
    LinkStack();

    LinkStack(const LinkStack<ElemType> &copy);

    int Length() const;

    bool Empty() const;

    void Clear();

    void Push(const ElemType &key);

    ElemType Pop();

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
    Node<ElemType> *newNode = new Node<ElemType>(key, top);
    if (newNode == NULL) {
        cout << "¶¯Ì¬ÄÚ´æºÄ¾¡" << endl;
    } else {
        top = newNode;
        count++;
    }
}

template<class ElemType>
ElemType LinkStack<ElemType>::Pop() {
    if (Empty()) {
        cout << "Õ»ÒÑ¿Õ" << endl;
        return 0;
    } else {
        Node<ElemType> *tmpPtr;
        tmpPtr = top;
        ElemType e = tmpPtr->data;
        top = top->next;
        count--;
        delete tmpPtr;
        return e;
    }
}

template<class ElemType>
LinkStack<ElemType>::LinkStack(const LinkStack<ElemType> &copy) {
    if (copy.Empty()) {
        //copy is empty stack
        top = NULL;
    } else {
        //copy isn't empty stack
        top = new Node<ElemType>(copy.top->data, NULL);
        Node<ElemType> *buttomPtr = top;//µ±Ç°Õ»µ×
        for (Node<ElemType> *tmpPtr = copy.top->next; tmpPtr != NULL; tmpPtr = tmpPtr->next) {
            buttomPtr->next = new Node<ElemType>(tmpPtr->data, NULL);
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
            top = new Node<ElemType>(copy.top->data, NULL);
            Node<ElemType> *buttomPtr = top;//µ±Ç°Õ»µ×
            for (Node<ElemType> *tmpPtr = copy.top->next; tmpPtr != NULL; tmpPtr = tmpPtr->next) {
                buttomPtr->next = new Node<ElemType>(tmpPtr->data, NULL);
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

//int main() {
//    SqStack<char> stack;
//    char *str = new char[105], ch;
//    bool flag = true;
//    cin >> str;
//    for (int i = 0; i < strlen(str) && flag; i++) {
//        if (str[i] == '{' || str[i] == '[' || str[i] == '(') {
//            stack.Push(str[i]);
//        }
//        if (str[i] == '}') {
//            if (!stack.Empty()) {
//                ch = stack.Pop();
//                if (ch != '(') {
//                    flag = false;
//                }
//            }
//        } else if (str[i] == ']') {
//            if (!stack.Empty()) {
//                ch = stack.Pop();
//                if (ch != '(') {
//                    flag = false;
//                }
//            }
//        } else if (str[i] == ')') {
//            if (!stack.Empty()) {
//                ch = stack.Pop();
//                if (ch != '(') {
//                    flag = false;
//                }
//            }
//        }
//    }
//    if (!stack.Empty()) {
//        flag = false;
//    }
////    while ((ch = getchar()) != '\n') {
////        stack.Push(ch);
////    }
////    while (stack.Length() > 0) {
////        ch = stack.Pop();
////        if ((ch == '(' || ch == ')') || (ch == '[' || ch == ']') || ch == '{' || ch == '}') {
////            str[len++] = ch;
////        }
////    }
////    if (len % 2 == 1) {
////        flag = false;
////    } else {
////        for (int i = 0; i < len / 2; i++) {
////            if ((str[i] == ')' && str[len - i - 1] == '(') || (str[i] == ']' && str[len - i - 1] == '[') ||
////                (str[i] == '}' && str[len - i - 1] == '{')) {
////                flag = true;
////            } else {
////                flag = false;
////            }
////        }
////    }
//    if (flag) {
//        cout << "TRUE" << endl;
//    } else {
//        cout << "FALSE" << endl;
//    }
//    return 0;
//}

//int main() {
//    SqStack<int> test1;
//    for (int i = 1; i <= 5; i++) {
//        test1.Push(i);
//    }
//    SqStack<int> test2 = test1;
//    for (int i = 1; i <= 5; i++) {
//        int e = test2.Pop();
//        cout << e << ' ';
//    }
//    cout << endl;
//    SqStack<int> test3;
//    test3 = test1;
//    for (int i = 1; i <= 5; i++) {
//        int e = test3.Pop();
//        cout << e << ' ';
//    }
//    cout << endl;

//    LinkStack<int> ls1, ls2;
//    for (int i = 1; i <= 5; i++) {
//        ls1.Push(i * 3);
//    }
//    ls2 = ls1;
//    for (int i = 1; i <= 5; i++) {
//        int elem = ls2.Pop();
//        cout << elem << ' ';
//    }
//    cout << endl;
//
//    LinkStack<int> ls3(ls1);
//    for (int i = 1; i <= 5; i++) {
//        int elem = ls3.Pop();
//        cout << elem << ' ';
//    }
//    cout << endl;
//    return 0;
//}


//int main() {
////    SqStack<int> stack;
////    int n, temp;
////    cin >> n;
////    for (int i = 1; i <= n; i++) {
////        cin >> temp;
////        stack.Push(temp);
////    }
////    for (int i = 1; i <= n; i++) {
////        temp = stack.Pop();
////        cout << temp << ' ';
////    }
////    putchar('\n');
//
//
//    LinkStack<int> stack1, stack2;
//    for (int i = 1; i <= 5; i++) {
//        stack1.Push(2 * i);
//        stack2.Push(2 * i - 1);
//    }
//
//    LinkStack<int> stack3(stack1);
//    int temp;
//    for (int i = 1; i <= 5; i++) {
//        temp = stack1.Pop();
//        cout << temp << ' ';
//    }
//    for (int i = 1; i <= 5; i++) {
//        temp = stack3.Pop();
//        cout << temp << ' ';
//    }
//    return 0;
//}