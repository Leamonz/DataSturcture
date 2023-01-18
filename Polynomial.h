//
// Created by HP on 2023/1/10.
//

#ifndef UNTITLED_POLYNOMIAL_H
#define UNTITLED_POLYNOMIAL_H

#include "MyList.h"

struct Polyitem {
    double coef{};
    int exp{};

    Polyitem();

    Polyitem(double co, int ex);
};

Polyitem::Polyitem() {
    exp = -1;
}

Polyitem::Polyitem(double co, int ex) {
    coef = co;
    exp = ex;
}

class Polynomial {
    friend ostream &operator<<(ostream &out, const Polynomial &poly);

protected:
    SimpleLinkList<Polyitem> *polyList{};
public:
    Polynomial();

    ~Polynomial();

    int Length() const;

    bool IsZero() const;

    void SetZero();

    void InsItem(const Polyitem &item);

    Polynomial operator+(const Polynomial &p) const;

    Polynomial operator-(const Polynomial &p) const;

    Polynomial operator*(const Polynomial &p) const;

    Polynomial(const Polynomial &copy);

    explicit Polynomial(const SimpleLinkList<Polyitem> &list);

    Polynomial &operator=(const Polynomial &copy);

    Polynomial &operator=(const SimpleLinkList<Polyitem> &list);
};

ostream &operator<<(ostream &out, const Polynomial &poly) {
    Polyitem item;
    if (poly.polyList->GetElem(1, item)) {
        out << item.coef << "x^" << item.exp;
    } else {
        return out;
    }
    for (int i = 2; i <= poly.polyList->Length(); i++) {
        poly.polyList->GetElem(i, item);
        if (item.coef > 0) {
            out << "+";
        }
        out << item.coef << "x^" << item.exp;
    }
    return out;
}

Polynomial::Polynomial() {
    polyList = new SimpleLinkList<Polyitem>;
}

Polynomial::~Polynomial() {
    delete polyList;
}

int Polynomial::Length() const {
    return polyList->Length();
}

bool Polynomial::IsZero() const {
    return polyList->Empty();
}

void Polynomial::SetZero() {
    polyList->Clear();
}

void Polynomial::InsItem(const Polyitem &item) {
    int pos = 1;
    Polyitem tmpItem;
    if (polyList->Empty()) {
        polyList->Insert(1, item);
        return;
    }
    while (pos <= Length() && polyList->GetElem(pos, tmpItem) && tmpItem.exp < item.exp) {
        pos++;
    }
    if (tmpItem.exp != item.exp) {
        polyList->Insert(pos, item);
    } else {
        polyList->Delete(pos);
        if (tmpItem.coef + item.coef != 0) {
            tmpItem.coef = tmpItem.coef + item.coef;
            polyList->Insert(pos, tmpItem);
        }
    }
}

Polynomial Polynomial::operator+(const Polynomial &p) const {
    Polyitem aItem, bItem;
    Polynomial ans{};
    int aPos = 1, bPos = 1;
    while (aPos <= polyList->Length() && bPos <= p.polyList->Length()) {
        polyList->GetElem(aPos, aItem);
        p.polyList->GetElem(bPos, bItem);
        if (aItem.exp == bItem.exp) {
            if (aItem.coef + bItem.coef != 0) {
                Polyitem cItem(aItem.coef + bItem.coef, aItem.exp);
                ans.InsItem(cItem);
            }
        } else {
            ans.InsItem(aItem);
            ans.InsItem(bItem);
        }
        aPos++;
        bPos++;
    }
    while (aPos <= polyList->Length()) {
        polyList->GetElem(aPos, aItem);
        ans.InsItem(aItem);
        aPos++;
    }
    while (bPos <= p.polyList->Length()) {
        p.polyList->GetElem(bPos, bItem);
        ans.InsItem(bItem);
        bPos++;
    }
    return ans;
}

Polynomial Polynomial::operator-(const Polynomial &p) const {
    Polyitem aItem, bItem;
    Polynomial ans{};
    int aPos = 1, bPos = 1;
    while (aPos <= polyList->Length() && bPos <= p.polyList->Length()) {
        polyList->GetElem(aPos, aItem);
        p.polyList->GetElem(bPos, bItem);
        bItem.coef = -bItem.coef;
        if (aItem.exp == bItem.exp) {
            if (aItem.coef + bItem.coef != 0) {
                Polyitem cItem(aItem.coef + bItem.coef, aItem.exp);
                ans.InsItem(cItem);
            }
        } else {
            ans.InsItem(aItem);
            ans.InsItem(bItem);
        }
        aPos++;
        bPos++;
    }
    while (aPos <= polyList->Length()) {
        polyList->GetElem(aPos, aItem);
        ans.InsItem(aItem);
        aPos++;
    }
    while (bPos <= p.polyList->Length()) {
        p.polyList->GetElem(bPos, bItem);
        bItem.coef = -bItem.coef;
        ans.InsItem(bItem);
        bPos++;
    }
    return ans;
}

Polynomial Polynomial::operator*(const Polynomial &p) const {
    Polyitem aItem, bItem;
    Polynomial ans{};
    int aPos = 1, bPos = 1;
    for (; aPos <= polyList->Length(); aPos++) {
        polyList->GetElem(aPos, aItem);
        for (bPos = 1; bPos <= p.polyList->Length(); bPos++) {
            p.polyList->GetElem(bPos, bItem);
            Polyitem cItem(aItem.coef * bItem.coef, aItem.exp + bItem.exp);
            ans.InsItem(cItem);
        }
    }
    return ans;
}

Polynomial::Polynomial(const Polynomial &copy) {
    polyList = new SimpleLinkList<Polyitem>;
    Polyitem tmpItem;
    for (int pos = 1; pos <= copy.polyList->Length(); pos++) {
        copy.polyList->GetElem(pos, tmpItem);
        InsItem(tmpItem);
    }
}

Polynomial::Polynomial(const SimpleLinkList<Polyitem> &list) {
    polyList = new SimpleLinkList<Polyitem>;
    Polyitem item;
    for (int pos = 1; pos <= list.Length(); pos++) {
        list.GetElem(pos, item);
        InsItem(item);
    }
}

Polynomial &Polynomial::operator=(const Polynomial &copy) {
    if (&copy != this) {
        if (polyList != nullptr) {
            delete polyList;
            polyList = nullptr;
        }
        polyList = new SimpleLinkList<Polyitem>;
        Polyitem tmpItem;
        for (int pos = 1; pos <= copy.polyList->Length(); pos++) {
            copy.polyList->GetElem(pos, tmpItem);
            InsItem(tmpItem);
        }
    }
    return *this;
}

Polynomial &Polynomial::operator=(const SimpleLinkList<Polyitem> &list) {
    if (polyList != nullptr) {
        delete polyList;
        polyList = nullptr;
    }
    polyList = new SimpleLinkList<Polyitem>;
    Polyitem item;
    for (int pos = 1; pos <= list.Length(); pos++) {
        list.GetElem(pos, item);
        InsItem(item);
    }
    return *this;
}

#endif //UNTITLED_POLYNOMIAL_H
