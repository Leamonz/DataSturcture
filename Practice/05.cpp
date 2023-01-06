//
// Created by HP on 2022/9/12.
//


//#include<iostream>
//
//using namespace std;
//


//
#include<iostream>
#include<cmath>

using namespace std;

template<class ElemType>
struct DblNode {
    ElemType data;
    DblNode<ElemType> *prev;
    DblNode<ElemType> *next;

    DblNode();

    DblNode(ElemType data, DblNode<ElemType> *p, DblNode<ElemType> *n);

    DblNode(const DblNode<ElemType> &node);
};

template<class ElemType>
DblNode<ElemType>::DblNode() {
    prev = NULL;
    next = NULL;
}

template<class ElemType>
DblNode<ElemType>::DblNode(ElemType data, DblNode<ElemType> *p, DblNode<ElemType> *n) {
    this->data = data;
    this->prev = p;
    this->next = n;
}

template<class ElemType>
DblNode<ElemType>::DblNode(const DblNode<ElemType> &node) {
    this->data = node.data;
    this->prev = node.prev;
    this->next = node.next;
}

////双向循环链表
template<class ElemType>
class BiCircleLinkList {
protected:
    DblNode<ElemType> *head;
    mutable DblNode<ElemType> *curPtr;
    mutable int curPos;
    int count{};

    DblNode<ElemType> *GetElemPtr(int pos) const {
//        pos=0表示头结点
        while (curPos < pos) {
            curPtr = curPtr->next;
            curPos++;
        }
        while (curPos > pos) {
            curPtr = curPtr->prev;
            curPos--;
        }
        return curPtr;
    }

public:
    BiCircleLinkList() {
        head = new DblNode<ElemType>;
        head->prev = head;
        head->next = head;
        curPtr = head;
        curPos = 0;
        count = 0;
    }

    int Length() const {
        return count;
    }

    ElemType GetElem(int pos) const {
        if (pos < 1 || pos > Length() + 1) {
            cout << "位置非法" << endl;
            exit(1);
        }
        DblNode<ElemType> *tmpPtr = GetElemPtr(pos);
        return tmpPtr->data;
    }

    void SetElem(int pos, ElemType key) {
        if (pos < 1 || pos > Length()) {
            cout << "位置非法" << endl;
            exit(1);
        }
        DblNode<ElemType> *tmpPtr = GetElemPtr(pos);
        tmpPtr->data = key;
    }

    void Insert(int pos, ElemType key) {
        if (pos < 1 || pos > Length() + 1) {
            cout << "位置非法" << endl;
            exit(1);
        }
        DblNode<ElemType> *nextPtr = GetElemPtr(pos);
        DblNode<ElemType> *prevPtr = nextPtr->prev;
        auto *newNode = new DblNode<ElemType>(key, prevPtr, nextPtr);
        prevPtr->next = newNode;
        nextPtr->prev = newNode;
        curPtr = newNode;
        curPos = pos;
        count++;
    }

    void Delete(int pos) {
        if (pos < 1 || pos > Length() + 1) {
            cout << "位置非法" << endl;
            exit(1);
        }
        DblNode<ElemType> *tmpPtr = GetElemPtr(pos);
        DblNode<ElemType> *prevPtr = tmpPtr->prev;
        DblNode<ElemType> *nextPtr = tmpPtr->next;
        prevPtr->next = nextPtr;
        nextPtr->prev = prevPtr;
        delete tmpPtr;
        if (pos == Length()) {
            curPos = 0;
            curPtr = head;
        } else {
            curPos = pos;
            curPtr = prevPtr->next;
        }
        count--;
    }

    void Clear() {
        while (Length() > 0) {
            Delete(1);
        }
    }

    bool Empty() const {
        return count == 0;
    }

    void Traverse(void(*Visit)(ElemType &)) const {
        if (!Empty()) {
            for (curPtr = head->next, curPos = 1; curPtr != head; curPtr = curPtr->next, curPos++) {
                Visit(curPtr->data);
            }
        }
    }

    BiCircleLinkList<ElemType> &operator=(const BiCircleLinkList<ElemType> &copy) {
        if (&copy != this) {
            Clear();
            head = copy.head;
            curPtr = head;
            curPos = 0;
            DblNode<ElemType> *tmpPtr = copy.head->next;
            for (int i = 1; i <= copy.Length(); i++) {
                Insert(Length() + 1, tmpPtr->data);
                tmpPtr = tmpPtr->next;
            }
        }
        return *this;
    }

    BiCircleLinkList(const BiCircleLinkList<ElemType> &copy) {
        Clear();
        head = copy.head;
        curPtr = head;
        curPos = 0;
        DblNode<ElemType> *tmpPtr = copy.head->next;
        for (int i = 1; i <= copy.Length(); i++) {
            Insert(Length() + 1, tmpPtr->data);
            tmpPtr = tmpPtr->next;
        }
    }

    ~BiCircleLinkList() {
        Clear();
        delete head;
    }
};

struct Polyitem {
    double coef;
    int exp;

    Polyitem() = default;

    Polyitem(double c, int e) {
        coef = c;
        exp = e;
    }

    ~Polyitem() = default;
};

class Polynomial {
protected:
    BiCircleLinkList<Polyitem> LinkList;

public:
    Polynomial() = default;

    int Count() const {
        return LinkList.Length();
    }

    Polyitem GetItem(int pos) const {
        return LinkList.GetElem(pos);
    }

    void SetItem(int pos, const Polyitem &key) {
        LinkList.Delete(pos);
        InsItem(key);
    }

    void SetItem(int pos, double coef, int exp) {
        Polyitem tmp = LinkList.GetElem(pos);
        tmp.coef = coef;
        tmp.exp = exp;
        LinkList.Delete(pos);
        InsItem(tmp);
    }

    void InsItem(const Polyitem &key) {
        Polyitem temp;
        int i;
        for (i = 1; i <= Count(); i++) {
            temp = LinkList.GetElem(i);
            if (temp.exp >= key.exp) {
                break;
            }
        }
        if (i == Count() + 1) {
            LinkList.Insert(i, key);
        } else if (temp.exp == key.exp) {
            LinkList.Delete(i);
            temp.coef += key.coef;
            if (fabs(temp.coef - 0) <= 1e7) {
                LinkList.Insert(i, temp);
            }
        } else if (temp.exp > key.exp) {
            LinkList.Insert(i, key);
        }
    }

    void Delete(int pos) {
        LinkList.Delete(pos);
    }

    void Display() const {
        Polyitem temp;
        for (int i = 1; i <= Count(); i++) {
            temp = LinkList.GetElem(i);
            if (i == 1) {
                if (temp.coef != 1) {
                    cout << temp.coef;
                }
                if (temp.exp != 1) {
                    cout << "x^" << temp.exp;
                } else {
                    cout << "x";
                }
            } else {
                if (temp.coef > 0) {
                    putchar('+');
                }
                if (temp.coef != 1) {
                    cout << temp.coef;
                }
                if (temp.exp != 1) {
                    cout << "x^" << temp.exp;
                } else {
                    cout << "x";
                }
            }
        }
        putchar('\n');
    }

    Polynomial operator+(const Polynomial &poly) const {
        BiCircleLinkList<Polyitem> ls;
        int aPos = 1, bPos = 1;
        Polyitem aItem = LinkList.GetElem(aPos), bItem = poly.LinkList.GetElem(bPos), temp(0, 0);
        while (aPos <= Count() && bPos <= poly.Count()) {
            if (aItem.exp == bItem.exp) {
                temp.coef = aItem.coef + bItem.coef;
                temp.exp = aItem.exp;
                if (temp.coef != 0) {
                    ls.Insert(ls.Length() + 1, temp);
                }
                aItem = LinkList.GetElem(++aPos);
                bItem = poly.LinkList.GetElem(++bPos);
            } else if (aItem.exp < bItem.exp) {
                ls.Insert(ls.Length() + 1, aItem);
                aItem = LinkList.GetElem(++aPos);
            } else if (aItem.exp > bItem.exp) {
                ls.Insert(ls.Length() + 1, bItem);
                bItem = poly.LinkList.GetElem(++bPos);
            }
        }

        while (aPos <= Count()) {
            ls.Insert(ls.Length() + 1, aItem);
            aItem = LinkList.GetElem(++aPos);
        }
        while (bPos <= poly.Count()) {
            ls.Insert(ls.Length() + 1, bItem);
            bItem = poly.LinkList.GetElem(++bPos);
        }
        Polynomial ans;
        ans.LinkList = ls;
        return ans;
    }

    Polynomial operator-(const Polynomial &poly) const {
        BiCircleLinkList<Polyitem> ls;
        int aPos = 1, bPos = 1;
        Polyitem aItem = LinkList.GetElem(aPos), bItem = poly.LinkList.GetElem(bPos), temp(0, 0);
        while (aPos <= Count() && bPos <= poly.Count()) {
            if (aItem.exp == bItem.exp) {
                temp.coef = aItem.coef - bItem.coef;
                temp.exp = aItem.exp;
                if (temp.coef != 0) {
                    ls.Insert(ls.Length() + 1, temp);
                }
                aItem = LinkList.GetElem(++aPos);
                bItem = poly.LinkList.GetElem(++bPos);
            } else if (aItem.exp < bItem.exp) {
                ls.Insert(ls.Length() + 1, aItem);
                aItem = LinkList.GetElem(++aPos);
            } else if (aItem.exp > bItem.exp) {
                temp.coef = -bItem.coef;
                temp.exp = bItem.exp;
                ls.Insert(ls.Length() + 1, temp);
                bItem = poly.LinkList.GetElem(++bPos);
            }
        }

        while (aPos <= Count()) {
            ls.Insert(ls.Length() + 1, aItem);
            aItem = LinkList.GetElem(++aPos);
        }
        while (bPos <= poly.Count()) {
            temp.coef = -bItem.coef;
            temp.exp = bItem.exp;
            ls.Insert(ls.Length() + 1, temp);
            bItem = poly.LinkList.GetElem(++bPos);
        }
        Polynomial ans;
        ans.LinkList = ls;
        return ans;
    }

    Polynomial operator*(const Polynomial &poly) const {
        Polynomial ans;
        BiCircleLinkList<Polyitem> ls;
        int aPos, bPos;
        Polyitem aItem(0, 0), bItem(0, 0), temp(0, 0);
        for (aPos = 1; aPos <= this->Count(); aPos++) {
            aItem = GetItem(aPos);
            for (bPos = 1; bPos <= poly.Count(); bPos++) {
                bItem = GetItem(bPos);
                temp.coef = aItem.coef * bItem.coef;
                temp.exp = aItem.exp + bItem.exp;
                ans.InsItem(temp);
            }
        }
//        ans.LinkList = ls;
        return ans;
    }

    Polynomial(const Polynomial &copy) {
        LinkList = copy.LinkList;
    }

    Polynomial &operator=(const Polynomial &copy) {
        if (&copy != this) {
            LinkList = copy.LinkList;
        }
        return *this;
    }

    ~Polynomial() {
        LinkList.Clear();
    }
};

//int main() {
////    Polynomial test;
////    srand((unsigned int) time_t(NULL));
////    for (int i = 1; i <= 5; i++) {
////        test.InsItem(Polyitem(i * 2.0, i));
////    }
////    test.Display();
////    Polyitem temp = Polyitem(5.0, 1);
////    test.InsItem(temp);
////    Polyitem temp1 = test.GetItem(1);
////    cout << temp1.coef << "x^" << temp1.exp << endl;
////    test.Display();
////    test.SetItem(2, 5.0, 3);
////    test.Display();
////    temp1 = Polyitem(4.0, 4);
////    test.SetItem(1, temp1);
////    test.Display();
//
////    BiCircleLinkList<int> l, l2;
////    l.Insert(l.Length() + 1, 1);
////    l.Insert(l.Length() + 1, 2);
////    l.Insert(l.Length() + 1, 3);
////    cout << l.GetElem(1);
////    l2 = l;
////    cout << l2.GetElem(2);
//    Polynomial test1, test2, test3, test4, test5;
//    for (int i = 1; i <= 5; i++) {
//        test1.InsItem(Polyitem(i * 1.0, i));
//    }
//    test1.InsItem(Polyitem(-4.0, 7));
//    test1.InsItem(Polyitem(-9.0, 6));
//    for (int i = 1; i <= 4; i++) {
//        test2.InsItem(Polyitem(i * 3.0, i));
//    }
//    test2.InsItem(Polyitem(6.0, 6));
//    test2.InsItem(Polyitem(3.0, 8));
//
//    test1.Display();
//    test2.Display();
//    Polynomial test6(test1);
//    test6.Display();
////    test1 + test2;
////    Polynomial test7(test1 + test2);
////    test7.Display();
////    Polynomial(test1 + test2).Display();
////    Polynomial(test1 - test2).Display();
//    Polynomial(test1 * test2).Display();
//    return 0;
//}



//int main() {
//    BiCircleLinkList<int> test;
//    for (int i = 1; i <= 5; i++) {
//        test.Insert(i, i);
//    }
//    for (int i = 1; i <= test.Length(); i++) {
//        int val = test.GetElem(i);
//        cout << val << ' ';
//    }
//    cout << endl;
//    test.SetElem(1, 10);
//    cout << test.GetElem(1) << endl;
//    test.Delete(2);
//    for (int i = 1; i <= test.Length(); i++) {
//        int val = test.GetElem(i);
//        cout << val << ' ';
//    }
//    cout << endl;
//    test.Clear();
//    if (!test.Empty()) {
//        for (int i = 1; i <= 5; i++) {
//            int val = test.GetElem(i);
//            cout << val << ' ';
//        }
//        cout << endl;
//    } else {
//        cout << "Empty list" << endl;
//    }
//    return 0;
//}


