//
// Created by HP on 2022/9/6.
//


//链表顺序表实现 一元多项式
//#include<iostream>
//#include<cstdlib>
//#include"BiLinkList.hpp"
//
//using namespace std;
//
//
//struct PolyItem {
//    double coef;
//    int exp;
//
//    PolyItem();
//
//    PolyItem(double c, int e);
//};
//
//PolyItem::PolyItem() {
//    exp = 0;
//    coef = 0;
//}
//
//PolyItem::PolyItem(double c, int e) {
//    coef = c;
//    exp = e;
//}
//
//class Polynomial {
//protected:
//    BiLinkList<PolyItem> LinkList;
//public:
//    Polynomial() = default;
//
//    virtual ~Polynomial() = default;
//
//    int Length() const;
//
//    bool isZero() const;
//
//    void setZero();
//
//    void Display() const;
//
//    void InsItem(const PolyItem &item);
//
//    Polynomial operator+(const Polynomial &poly) const;
//
//    Polynomial operator-(const Polynomial &poly) const;
//
//    Polynomial operator*(const Polynomial &poly) const;
//
//    Polynomial(const Polynomial &copy);
//
//    Polynomial &operator=(const Polynomial &copy);
//
//    Polynomial &operator=(const BiLinkList<PolyItem> &copy);
//};
//
//int Polynomial::Length() const {
//    return LinkList.Length();
//}
//
//bool Polynomial::isZero() const {
//    return LinkList.Empty();
//}
//
//void Polynomial::setZero() {
//    LinkList.Clear();
//}
//
//void Polynomial::Display() const {
//    PolyItem temp;
//    for (int i = 1; i <= LinkList.Length(); i++) {
//        temp = LinkList.GetElem(i);
////        cout << temp.coef << ' ' << temp.exp << endl;
//        if (temp.coef > 0) {
//            putchar('+');
//        }
//        cout << temp.coef << "x^" << temp.exp << ' ';
//    }
//    putchar('\n');
//}
//
//void Polynomial::InsItem(const PolyItem &item) {
//    //关键问题，找到插入的位置
//    int pos = 1;
//    PolyItem temp = LinkList.GetElem(pos);
//    for (; pos <= LinkList.Length(); pos++) {
//        temp = LinkList.GetElem(pos);
//        if (temp.exp >= item.exp) {
//            break;
//        }
//    }
//    if (LinkList.Length() != 0 && temp.exp == item.exp) {
//        LinkList.Delete(pos);
//        LinkList.Insert(pos, PolyItem(temp.coef + item.coef, item.exp));
//        return;
//    }
////    cout << item.coef << item.exp << endl;
//    LinkList.Insert(pos, item);
//    return;
//}
//
//Polynomial Polynomial::operator+(const Polynomial &poly) const {
//    Polynomial ans;
//    int aPos = 1, bPos = 1;
//    PolyItem aItem, bItem;
//    while (aPos <= this->Length() && bPos <= poly.Length()) {
//        aItem = LinkList.GetElem(aPos);
//        bItem = poly.LinkList.GetElem(bPos);
//        if (aItem.exp > bItem.exp) {
//            ans.InsItem(bItem);
//            bPos++;
//        } else if (aItem.exp < bItem.exp) {
//            ans.InsItem(aItem);
//            aPos++;
//        } else {
//            ans.InsItem(PolyItem(aItem.coef + bItem.coef, aItem.exp + bItem.exp));
//            aPos++;
//            bPos++;
//        }
//    }
//    while (aPos <= this->Length()) {
//        ans.InsItem(aItem);
//        aPos++;
//    }
//    while (bPos <= poly.Length()) {
//        ans.InsItem(bItem);
//        bPos++;
//    }
//    return ans;
//}
//
//Polynomial Polynomial::operator-(const Polynomial &poly) const {
//    Polynomial ans;
//    int aPos = 1, bPos = 1;
//    PolyItem aItem, bItem;
//    while (aPos <= this->Length() && bPos <= poly.Length()) {
//        aItem = LinkList.GetElem(aPos);
//        bItem = poly.LinkList.GetElem(bPos);
//        if (aItem.exp > bItem.exp) {
//            ans.InsItem(PolyItem(-bItem.coef, bItem.exp));
//            bPos++;
//        } else if (aItem.exp < bItem.exp) {
//            ans.InsItem(aItem);
//            aPos++;
//        } else {
//            ans.InsItem(PolyItem(aItem.coef - bItem.coef, aItem.exp - bItem.exp));
//            aPos++;
//            bPos++;
//        }
//    }
//    while (aPos <= this->Length()) {
//        ans.InsItem(aItem);
//        aPos++;
//    }
//    while (bPos <= poly.Length()) {
//        ans.InsItem(bItem);
//        bPos++;
//    }
//    return ans;
//}
//
//Polynomial Polynomial::operator*(const Polynomial &poly) const {
//    PolyItem aItem, bItem, temp;
//    Polynomial ans;
//    int aPos = 1, bPos = 1;
//    for (; aPos <= Length(); aPos++) {
//        aItem = LinkList.GetElem(aPos);
//        for (bPos = 1; bPos <= poly.Length(); bPos++) {
//            bItem = poly.LinkList.GetElem(bPos);
//            temp = PolyItem(aItem.coef * bItem.coef, aItem.exp + bItem.exp);
//            ans.InsItem(temp);
//        }
//    }
//    return ans;
//}
//
//
//Polynomial &Polynomial::operator=(const Polynomial &copy) {
//    if (&copy != this) {
//        LinkList.Clear();
//        LinkList = copy.LinkList;
//    }
//    return *this;
//}
//
//Polynomial &Polynomial::operator=(const BiLinkList<PolyItem> &copy) {
//    LinkList.Clear();
//    LinkList = copy;
//    return *this;
//}
//
//Polynomial::Polynomial(const Polynomial &copy) {
//    LinkList.Clear();
//    LinkList = copy.LinkList;
//}
//
//int main() {
//    PolyItem temp;
//    Polynomial la, lb, lc;
//    for (int i = 1; i <= 5; i++) {
//        temp = PolyItem(i, i);
//        la.InsItem(temp);
//    }
//    for (int j = 1; j <= 4; j++) {
//        temp = PolyItem(j + 5, j);
//        lb.InsItem(temp);
//    }
//    la.Display();
//    lb.Display();
//    return 1;
//}


#include<iostream>
//#include"BiLinkList.hpp"
using namespace std;

//int main(){
//    BiLinkList<int> t;
//    t.Insert(1,5);
//    t.Insert(2,6);
//    int temp = t.GetElem(1);
//    cout<<temp;
//    return 0;
//}
