//
// Created by HP on 2022/9/6.
//
//循环链表

#include<iostream>
#include<list>
using namespace std;

template<class ElemType>
struct Node {
    ElemType data;
    Node<ElemType> *next;

    Node();

    explicit Node(ElemType item, Node<ElemType> *link = NULL);
};

template<class ElemType>
Node<ElemType>::Node() {
    next = NULL;//指针域初始化为空
}

template<class ElemType>
Node<ElemType>::Node(ElemType item, Node<ElemType> *link) {
    data = item;
    next = link;
}

template<class ElemType>
class CircleLinkList {
protected:
    Node<ElemType> *head;

    //辅助函数
    Node<ElemType> *GetElemPtr(int pos) const;//返回第pos个结点的指针

public:
    CircleLinkList();

    virtual ~CircleLinkList();

    int Length() const;

    bool Empty() const;

    void Clear();

    void Traverse(void(*Visit)(ElemType &));

    ElemType GetElem(int pos) const;

    void SetElem(int pos, ElemType key);

    void Delete(int pos);

    void Insert(int pos, ElemType key);

    CircleLinkList(const CircleLinkList<ElemType> &copy);

    CircleLinkList<ElemType> &operator=(const CircleLinkList<ElemType> &copy);
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
        //查找成功
        return tmpPtr;
    } else {
        //查找失败
        return NULL;
    }


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

//    int count = 0;
//    Node<ElemType> *tmpPtr = head->next;
//    while (tmpPtr != NULL) {
//        count++;
//        tmpPtr = tmpPtr->next;
//    }
//    return count;
}

template<class ElemType>
bool CircleLinkList<ElemType>::Empty() const {
    /*============================*/
    return head->next == head;
    /*============================*/
//    return head->next == NULL;
}

template<class ElemType>
void CircleLinkList<ElemType>::Clear() {
    while (Length() > 0) {
        Delete(1);//不停删除第一个结点，直到链表为空
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
        cout << "位置错误\n";
        exit(0);
    } else {
        Node<ElemType> *tmpPtr = GetElemPtr(pos);
        return tmpPtr->data;
    }
}

template<class ElemType>
void CircleLinkList<ElemType>::SetElem(int pos, ElemType key) {
    if (pos < 1 || pos > Length()) {
        cout << "位置错误\n";
        exit(0);
    } else {
        Node<ElemType> *tmpPtr = GetElemPtr(pos);
        tmpPtr->data = key;
    }
}

template<class ElemType>
void CircleLinkList<ElemType>::Insert(int pos, ElemType key) {
    if (pos < 1 || pos > Length() + 1) {
        cout << "位置错误\n";
        exit(0);
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
        cout << "位置错误\n";
        exit(0);
    } else {
        Node<ElemType> *tmpPtr = GetElemPtr(pos - 1);
        Node<ElemType> *nextPtr = tmpPtr->next;
        tmpPtr->next = nextPtr->next;
        delete nextPtr;
    }
}

template<class ElemType>
CircleLinkList<ElemType>::CircleLinkList(const CircleLinkList<ElemType> &copy) {
    head = copy.head;
}

template<class ElemType>
CircleLinkList<ElemType>::~CircleLinkList() {
    delete head;
}

template<class ElemType>
CircleLinkList<ElemType> &CircleLinkList<ElemType>::operator=(const CircleLinkList<ElemType> &copy) {
    if (&copy != this) {
        head = copy.head;
    }
    return *this;
}


template<class ElemType>
void Print(ElemType val) {
    cout << val << ' ';
}

//int main() {
//    CircleLinkList<int> l1, l2;
//    l1.Insert(l1.Length() + 1, 1);
//    l1.Insert(l1.Length() + 1, 2);
//    l1.Insert(l1.Length() + 1, 3);
//    cout << l1.GetElem(1) << endl;
//    l2 = l1;
//    cout << "hello" << endl;
////    cout << l2.GetElem(2) << endl;
////    CircleLinkList<int> l3(l1);
////    CircleLinkList<int> l4(l2);
////    cout << l3.GetElem(1) << endl;
////    cout << l4.GetElem(3) << endl;
//    return 0;
//}
//
//int main() {
//    CircleLinkList<int> t;
//    t.Insert(1, 5);
//    t.Insert(2, 6);
//    cout << t.GetElem(1);
//    return 0;
//}

//
//
//template<class ElemType>
//int Joseph(CircleLinkList<ElemType> &list, int n, int m) {
//    int curPos = 1, flag = 1;
//    while (list.Length() > 1) {
//        if (curPos > list.Length()) {
//            curPos = 1;
//            continue;
//        }
//        if (flag == m) {
//            flag = 1;
//            list.Delete(curPos);
//            continue;
//        }
//        curPos++;
//        flag++;
//    }
////    for (int i = 1; i < n; i++) {
////        for (flag = 1; flag <= m; flag++) {
////            curPos++;
////            if (curPos > list.Length()) {
////                curPos = 1;
////            }
////        }
////        list.Delete(curPos--);
////    }
//    return list.GetElem(1);
//}
//
//int main() {
//    CircleLinkList<int> list;
//    int n, m;
//    cin >> n >> m;
//    for (int i = 1; i <= n; i++) {
//        list.Insert(i, i);
//    }
//    cout << Joseph(list, n, m);
//    return 0;
//}



//双向链表
//#include<iostream>
//
//using namespace std;
//
//template<class ElemType>
//struct DblNode {
//    ElemType data;
//    DblNode<ElemType> *prev;
//    DblNode<ElemType> *next;
//
//    DblNode();
//
//    DblNode(ElemType data, DblNode<ElemType> *p, DblNode<ElemType> *n);
//};
//
//template<class ElemType>
//DblNode<ElemType>::DblNode() {
//    prev = NULL;
//    next = NULL;
//}
//
//template<class ElemType>
//DblNode<ElemType>::DblNode(ElemType data, DblNode<ElemType> *p, DblNode<ElemType> *n) {
//    this->data = data;
//    prev = p;
//    next = n;
//}
//
//template<class ElemType>
//class BiLinkList {
//protected:
//    DblNode<ElemType> *head;
//    /* 新添加的数据成员记录当前位置/指针以及链表中的元素个数 */
//    mutable int curPos;
//    mutable DblNode<ElemType> *curPtr;
//    int count;
//
//
//    DblNode<ElemType> *GetElemPtr(int pos) const;
//
//public:
//    BiLinkList();
//
//    BiLinkList(const BiLinkList<ElemType> &copy);
//
//    virtual ~BiLinkList();
//
//    int Length() const;
//
//    bool Empty() const;
//
//    void Clear();
//
//    void Traverse(void(*Visit)(ElemType)) const;
//
//    ElemType GetElem(int pos) const;
//
//    void SetElem(int pos, ElemType key);
//
//    void Insert(int pos, ElemType key);
//
//    void Delete(int pos);
//
//    BiLinkList<ElemType> &operator=(const BiLinkList<ElemType> &copy);
//};
//
//
//template<class ElemType>
//DblNode<ElemType> *BiLinkList<ElemType>::GetElemPtr(int pos) const{
//    if (pos < 1 || pos > Length()) {
//        cout << "位置错误\n";
//        exit(0);
//    }
//    if (curPos > pos) {
//        //通过前驱指针去找目标结点
//        while (curPtr != head && curPos != pos) {
//            curPtr = curPtr->prev;
//            curPos--;
//        }
//    } else if (curPos < pos) {
//        //通过后继指针去找目标结点
//        while (curPtr != head && curPos != pos) {
//            curPtr = curPtr->next;
//            curPos++;
//        }
//    }
//    return curPtr;
//
////    DblNode<ElemType> *tmpPtr = head;
////    int curPos = 0;
////    while (tmpPtr != head && curPos != pos) {
////        tmpPtr = tmpPtr->next;
////        curPos++;
////    }
////    if (tmpPtr != head && curPos == pos) {
////        return tmpPtr;
////    } else {
////        return NULL;
////    }
//}
//
//template<class ElemType>
//BiLinkList<ElemType>::BiLinkList() {
//    head = new DblNode<ElemType>;
//    head->next = head;
//    head->prev = head;
//    curPtr = head;
//    curPos = 0;
//    count = 0;
//}
//
//template<class ElemType>
//int BiLinkList<ElemType>::Length() const {
//    return count;
////    int count = 0;
////    DblNode<ElemType> *tmpPtr = head;
////    while (tmpPtr != head) {
////        tmpPtr = tmpPtr->next;
////        count++;
////    }
////    return count;
//}
//
//template<class ElemType>
//bool BiLinkList<ElemType>::Empty() const {
//    return head->next == head;
//}
//
//template<class ElemType>
//void BiLinkList<ElemType>::Clear() {
//    while (Length() > 0) {
//        Delete(1);
//    }
//}
//
//template<class ElemType>
//void BiLinkList<ElemType>::Traverse(void (*Visit)(ElemType)) const {
//    DblNode<ElemType> *tmpPtr;
//    for (tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next) {
//        Visit(tmpPtr->data);
//    }
//}
//
//template<class ElemType>
//ElemType BiLinkList<ElemType>::GetElem(int pos) const {
//    if (pos < 1 || pos > Length()) {
//        cout << "位置错误\n";
//        exit(0);
//    } else {
//        curPtr = GetElemPtr(pos);
//        return curPtr->data;
////        DblNode<ElemType> *tmpPtr;
////        tmpPtr = GetElemPtr(pos);
////        return tmpPtr->data;
//    }
//}
//
//template<class ElemType>
//void BiLinkList<ElemType>::SetElem(int pos, ElemType key) {
//    if (pos < 1 || pos > Length()) {
//        cout << "位置错误\n";
//        exit(0);
//    } else {
//        curPtr = GetElemPtr(pos);
//        curPtr->data = key;
////        DblNode<ElemType> *tmpPtr;
////        tmpPtr = GetElemPtr(pos);
////        tmpPtr->data = key;
//    }
//}
//
//template<class ElemType>
//void BiLinkList<ElemType>::Insert(int pos, ElemType key) {
//    if (pos < 1 || pos > Length() + 1) {
//        cout << "位置错误\n";
//        exit(0);
//    } else {
//        DblNode<ElemType> *nextPtr = GetElemPtr(pos);
//        DblNode<ElemType> *prevPtr = nextPtr->prev;
//        DblNode<ElemType> *newNode = new DblNode<ElemType>(key, prevPtr, nextPtr);
//        prevPtr->next = newNode;
//        nextPtr->prev = newNode;
//        count++;
//    }
//}
//
//template<class ElemType>
//void BiLinkList<ElemType>::Delete(int pos) {
//    if (pos < 1 || pos > Length()) {
//        cout << "位置错误\n";
//        exit(0);
//    } else {
//        DblNode<ElemType> *tmpPtr = GetElemPtr(pos);
//        DblNode<ElemType> *prevPtr = tmpPtr->prev;
//        DblNode<ElemType> *nextPtr = tmpPtr->next;
//        prevPtr->next = nextPtr;
//        nextPtr->prev = prevPtr;
//        if (pos == Length()) {
//            //删除尾结点，当前指针指向头结点
//            curPos = 0;
//            curPtr = head;
//        } else {
//            //删除非尾结点，当前指针指向pos位置的结点（删除前pos位置后一个结点）
//            curPos = pos;
//            curPtr = nextPtr;
//        }
//        count--;
//        delete tmpPtr;
//    }
//}
//
//
//template<class ElemType>
//BiLinkList<ElemType> &BiLinkList<ElemType>::operator=(const BiLinkList<ElemType> &copy) {
//    if (&copy != this) {
//        Clear();
//        head = copy.head;
//    }
//    return *this;
//}
//
//template<class ElemType>
//BiLinkList<ElemType>::BiLinkList(const BiLinkList<ElemType> &copy) {
//    head = copy.head;
//    count = copy.count;
//    curPos = 0;
//    curPtr = head;
//}
//
//template<class ElemType>
//BiLinkList<ElemType>::~BiLinkList() {
//    Clear();
//    delete head;
//}
//
//int main() {
//    BiLinkList<int> t;
//    t.Insert(1, 5);
//    t.Insert(2, 6);
//    cout << t.GetElem(1);
//    return 0;
//}

//
//template<class ElemType>
//void Print(ElemType val) {
//    cout << val << ' ';
//}
//
//int main() {
//
//    return 0;
//}
