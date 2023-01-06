//
// Created by HP on 2022/9/17.
//
#pragma once
#ifndef CLION_CharString_H
#define CLION_CharString_H

#include<cstring>
#include<iostream>
#include "MyList.h"

using namespace std;

void CStrCat(char *dest, const char *src);

void CStrcpy(char *dest, const char *src);

class CharString {
    friend ostream &operator<<(ostream &, const CharString &);

    friend istream &operator>>(istream &, CharString &);

protected:
    int len;
    char *str;
public:
    CharString();

    CharString(const CharString &copy);

    explicit CharString(const char *copy);

    explicit CharString(const SimpleLinkList<char> &copy);

    virtual ~CharString();

    int Length() const;

    bool Empty() const;

    void reversed();//翻转字符串

    CharString &operator=(const CharString &copy);

    CharString &operator=(const SimpleLinkList<char> &copy);

    int search(const CharString &sub, CharString &res);

    const char *CStr() const;

    explicit operator char *();

    char &operator[](unsigned int pos) const;
};

CharString::CharString() {
    str = nullptr;
    len = 0;
}

CharString::CharString(const CharString &copy) {
    len = copy.len;
    str = new char[len + 1];
    strcpy(str, copy.CStr());
}

CharString::CharString(const char *copy) {
    len = strlen(copy);
    str = new char[len + 1];
    strcpy(str, copy);
}

int CharString::Length() const {
    return len;
}

bool CharString::Empty() const {
    return len == 0;
}

const char *CharString::CStr() const {
    return (const char *) str;
}

CharString &CharString::operator=(const CharString &copy) {
    if (&copy != this) {
        len = copy.len;
        str = new char[len + 1];
        strcpy(str, copy.CStr());
    }
    return *this;
}

char &CharString::operator[](unsigned int pos) const {
    return str[pos];
}

CharString::~CharString() {
    delete[] str;
}

CharString::operator char *() {
    return str;
}

int CharString::search(const CharString &sub, CharString &res) {
    char *subStr = sub.str;
    char resStr[255] = "";
    const char *seed1 = "/*", *seed2 = "*/";
    int last = 0, count = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == subStr[0]) {
            bool flag = true;
            for (int j = 1; j < strlen(subStr); j++) {
                if (str[j + i] != subStr[j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                strncat(resStr, str + last, i - last);
                strcat(resStr, seed1);
                strcat(resStr, subStr);
                strcat(resStr, seed2);
                i = i + strlen(subStr);
                last = i;
                count++;
            }
        }
    }
    strncat(resStr, str + last, strlen(str) - last);
    res = CharString(resStr);
    return count;
}

ostream &operator<<(ostream &out, const CharString &s) {
    out << s.str;
    return out;
}

istream &operator>>(istream &in, CharString &s) {
    char *temp = new char[s.len + 1];
    cin >> temp;
    CStrcpy(s.str, temp);
    return in;
}

void CharString::reversed() {
    for (int i = 0; i < Length() / 2; i++) {
        char temp = str[i];
        str[i] = str[Length() - i - 1];
        str[Length() - i - 1] = temp;
    }
}

CharString::CharString(const SimpleLinkList<char> &copy) {
    str = new char[copy.Length() + 1];
    len = copy.Length();
    for (int i = 1; i <= copy.Length(); i++) {
        str[i - 1] = copy.GetElem(i);
    }
    str[copy.Length()] = '\0';
}

//利用C风格字符串可以轻松实现运算符的重载
bool operator==(const CharString &s1, const CharString &s2) {
    return strcmp(s1.CStr(), s2.CStr()) == 0;
}

bool operator!=(const CharString &s1, const CharString &s2) {
    return strcmp(s1.CStr(), s2.CStr()) != 0;
}

bool operator>(const CharString &s1, const CharString &s2) {
    return strcmp(s1.CStr(), s2.CStr()) > 0;
}

bool operator<(const CharString &s1, const CharString &s2) {
    return strcmp(s1.CStr(), s2.CStr()) < 0;
}

bool operator>=(const CharString &s1, const CharString &s2) {
    return strcmp(s1.CStr(), s2.CStr()) >= 0;
}

bool operator<=(const CharString &s1, const CharString &s2) {
    return strcmp(s1.CStr(), s2.CStr()) <= 0;
}

void CStrCat(char *dest, const char *src) {
    dest = dest + strlen(dest);
    while ((*dest++ = *src++) != '\0');
}

void CStrcpy(char *dest, const char *src) {
    delete[] dest;
    int i = 0;
    dest = new char[strlen(src) + 1];
    while ((*(dest + i) = *(src + i), i++) != '\0') { ;
    }
}

// 字符串拼接
void Concat(CharString &addTo, const CharString &addOn) {
    const char *first = addTo.CStr();
    const char *second = addOn.CStr();
    char *copy = new char[strlen(first) + strlen(second) + 1];
    strcpy(copy, first);
    CStrCat(copy, second);
    addTo = CharString(copy);
    delete[] copy;
}


//求子串在字符串中的位置，从pos开始---利用库函数
int Index(const CharString &target, const CharString &pattern, int pos = 0) {
    //先找到子串起始位置的指针
    const char *ptr = strstr(target.CStr(), pattern.CStr());
    if (ptr == nullptr) {
        cout << "匹配失败" << endl;
        return -1;
    } else {
        return int(ptr - target.CStr());
    }
}

//简单字符串模式匹配
int SimpleIndex(const CharString &target, const CharString &pattern, int pos = 0) {
    int i = pos, j = 0, max_len = target.Length() - pattern.Length();
    while (i <= max_len) {
        while (target[i] == pattern[j] && j < pattern.Length()) {
            i++;
            j++;
        }
        if (j == pattern.Length()) {
            return i - j;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    return -1;
}

//首尾字符串模式匹配
int FrontRearIndex(const CharString &target, const CharString &pattern, int pos = 0) {
    int len = pattern.Length();
    int front = 0, rear = len - 1;
    for (; pos <= target.Length() - len; pos++) {
        for (int i = 0; i <= len / 2; i++) {
            if (target[pos + i] != pattern[front + i] || target[pos + len - 1 - i] != pattern[rear - i]) {
                break;
            }
            if (front + i == rear - i) {
                // when front meets rear
                return pos;
            }
        }
    }
    return -1;
}

CharString Read(istream &input) {
    char temp[255];
    int len = 0;
    char c;
    while (input.peek() != EOF && (c = input.get()) != '\n') {
        temp[len++] = c;
    }
    temp[len] = '\0';
    CharString res = CharString(temp);
//    delete[] temp;
    return res;
}


#endif //CLION_CharString_H
