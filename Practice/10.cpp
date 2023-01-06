//
// Created by HP on 2022/9/20.
//

#include<iostream>
#include<cstring>
#include"../MyString.h"

using namespace std;


//KMP字符串模式匹配算法
void GetNext(const MyString &pattern, int next[]) {
    //核心---获取next数组
    next[0] = -1;
    for (int i = 1; i < pattern.Length(); i++) {
        next[i] = 0;
        for (int k = 1; k < i; k++) {
            bool flag = true;
            for (int j = 0; j < k; j++) {
                if (pattern[j] != pattern[i - k + j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                next[i] = k;
            }
        }
    }
}

int KMPIndexHelp(const MyString &target, const MyString &pattern, int next[], int pos) {
    //匹配算法
    int i = pos, j = 0;
    while (i <= target.Length() - pattern.Length()) {
        if (j == -1) {
            i++;
            j = 0;
        } else if (target[i] == pattern[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
        if (j > pattern.Length()) {
            return i - j;
        }
    }
    return -1;
}

int KMPIndex(const MyString &target, const MyString &pattern, int pos = 0) {
    int *next = new int[pattern.Length()];
    GetNext(pattern, next);
    int result = KMPIndexHelp(target, pattern, next, pos);
    delete[] next;
    return result;
}

//int main() {
//    const char *s1 = "hello world";
//    const char *s2 = "ell";
//    MyString test1(s1), test2(s2);
//    cout << FrontRearIndex(test1, test2) << endl;
//
//    cout << SimpleIndex(test1, test2) << endl;
//
//    cout << KMPIndex(test1, test2) << endl;
//    return 0;
//}