#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <cctype>
#include <cstdlib>
#include "MyQueue.h"
#include "MyList.h"
#include "MyString.h"
#include "MyStack.h"
#include "Matrix.h"
#include "BinaryTree.h"
#include "Array.h"
#include "Calculator.h"
#include "FileEditor.h"
#include "HuffmanCompress.h"
#include <ctime>
#include <stack>

using namespace std;

template<class ElemType>
void Print(ElemType &val) {
    cout << val << ' ';
}

int RecurBinSearch(int *arr, int l, int r, int key) {
    if (l >= r)
        return -1;
    int mid = (l + r) / 2;
    if (arr[mid] == key)
        return mid;
    else if (arr[mid] < key)
        return RecurBinSearch(arr, mid + 1, r, key);
    else if (arr[mid] > key)
        return RecurBinSearch(arr, l, mid - 1, key);
}

int Max(int x, int y, int z) {
    int m = x > y ? x : y;
    m = m > z ? m : z;
    return m;
}

template<class ElemType>
void Merge(const SimpleLinkList<ElemType> &la, const SimpleLinkList<ElemType> &lb, SimpleLinkList<ElemType> &lc) {
    int aPos = la.Length(), bPos = lb.Length();
    ElemType aItem = la.GetElem(aPos), bItem = lb.GetElem(bPos);
    while (aPos >= 1 && bPos >= 1) {
        if (aItem > bItem) {
            lc.Insert(lc.Length() + 1, aItem);
            if (--aPos < 1) break;
            aItem = la.GetElem(aPos);
        } else if (aItem < bItem) {
            lc.Insert(lc.Length() + 1, bItem);
            if (--bPos < 1) break;
            bItem = lb.GetElem(bPos);
        } else {
            lc.Insert(lc.Length() + 1, aItem);
            if (--aPos < 1 || --bPos < 1) break;
            aItem = la.GetElem(aPos);
            bItem = lb.GetElem(bPos);
        }
    }

    while (aPos >= 1) {
        lc.Insert(lc.Length() + 1, aItem);
        if (--aPos < 1) break;
        aItem = la.GetElem(aPos);
    }
    while (bPos >= 1) {
        lc.Insert(lc.Length() + 1, bItem);
        if (--bPos < 1) break;
        bItem = lb.GetElem(bPos);
    }
}

int Akm(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
        return Akm(m - 1, 1);
    } else {
        return Akm(m - 1, Akm(m, n - 1));
    }
}

int NonRecurAkm(int m, int n) {
    LinkStack<int> akm;
    int res, ma, na;
    akm.Push(m);
    akm.Push(n);
    while (akm.Length() > 1) {
        na = akm.Pop();
        ma = akm.Pop();
        if (ma == 0) {
            akm.Push(na + 1);
        } else if (na == 0) {
            akm.Push(ma - 1);
            akm.Push(1);
        } else {
            akm.Push(ma - 1);
            akm.Push(ma);
            akm.Push(na - 1);
        }
    }
    res = akm.Pop();
    return res;
}

int main() {
    int n, i, j;
    cin >> n;
    int mat[n][n];
    //创建两个数组分别用于存储每一行最小值的列下标以及每一列最大值的行下标
    int rows_min[n], cols_max[n];
    for (i = 0; i < n; i++) {
        // 初始化两个辅助数组
        rows_min[i] = cols_max[i] = 0;
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cin >> mat[i][j];
            if (mat[i][j] < mat[i][rows_min[i]]) {
                rows_min[i] = j;
            }
            if (mat[i][j] > mat[cols_max[j]][j]) {
                cols_max[j] = i;
            }
        }
    }
    pair<int, int> dots[n];
    int cnt = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            // 遍历矩阵寻找符合条件的点
            // A[i][j]恰好是第i行的最小值，恰好是第j列的最大值
            if (rows_min[i] == j && cols_max[j] == i) {
                dots[cnt++] = make_pair(i, j);
            }
        }
    }
    for (int k = 0; k < cnt; k++) {
        cout << "(" << dots[k].first << ", " << dots[k].second << ")" << " " << mat[dots[k].first][dots[k].second]
             << endl;
    }

//    clock_t startRecur = clock();
//    cout << Akm(3, 10) << endl;
//    clock_t endRecur = clock();
//    cout << "Recursive: " << (double) (endRecur - startRecur) / CLOCKS_PER_SEC << "s" << endl;
//    clock_t startNonRecur = clock();
//    cout << NonRecurAkm(3, 10) << endl;
//    clock_t endNonRecur = clock();
//    cout << "NonRecursive: " << (double) (endNonRecur - startNonRecur) / CLOCKS_PER_SEC << "s" << endl;
//    SimpleLinkList<int> la, lb, lc;
//    la.Insert(la.Length() + 1, 3);
//    la.Insert(la.Length() + 1, 5);
//    la.Insert(la.Length() + 1, 9);
//    lb.Insert(lb.Length() + 1, 2);
//    lb.Insert(lb.Length() + 1, 4);
//    lb.Insert(lb.Length() + 1, 8);
//    lb.Insert(lb.Length() + 1, 10);
//    lb.Insert(lb.Length() + 1, 20);
//    la.Traverse(Print);
//    cout << endl;
//    lb.Traverse(Print);
//    cout << endl;
//    Merge(la, lb, lc);
//    lc.Traverse(Print);
//    char pre[] = "ABCDEFGHI";
//    char in[] = "DCBAGFHEI";
//    BinaryTree<char> bt = CreateBinaryTree(pre, in, strlen(pre));
//    cout << "递归先序遍历" << endl;
//    bt.PreOrder(Print);
//    cout << endl;
//    cout << "递归中序遍历" << endl;
//    bt.InOrder(Print);
//    cout << endl;
//    cout << "递归后续遍历" << endl;
//    bt.PostOrder(Print);
//    cout << endl;
//    cout << "非递归先序遍历" << endl;
//    bt.NonRecurPreOrder(Print);
//    cout << endl;
//    cout << "非递归中序遍历" << endl;
////    bt.NonRecurInOrder(Print);
//    cout << endl;
//    cout << "非递归后序遍历" << endl;
////    bt.NonRecurPostOrder(Print);
//    cout << endl;


//    ifstream inf;
//    inf.open("test.txt", ios::binary | ios::in);
//    char ch;
//    int size = 1;
//    inf.read(&ch, sizeof(char));
//    putchar(ch);
//    while (!inf.eof()) {
//        inf.read(&ch, sizeof(char));
//        if (inf.eof()) break;
//        putchar(ch);
//    }
//    if (inf.eof()) {
//        cout << "hhh" << endl;
//    }
//    inf.clear();
//    inf.seekg(0, ios::beg);

//    while (!inf.eof()) {
//        inf.read(&ch, sizeof(char));
//        putchar(ch);
//    }

//    HuffmanCompress huffmanCompress;
//    bool active = true;
//    while (active) {
//        active = huffmanCompress.Run();
//    }
//    char ch[4] = {'a', 'b', 'c', 'd'};
//    unsigned long w[4] = {9, 8, 1, 6};
//    HuffmanTree<char, unsigned long> test(ch, w, 4);
//    CharString code = test.Encode('b');
//    cout << code;
//    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//    int pos = RecurBinSearch(arr, 0, 9, 3);
//    cout << pos << ": " << arr[pos] << endl;
//    int a, b, c;
//    cin >> a >> b >> c;
//    cout << "Max: " << Max(a, b, c) << endl;
    return 0;
}