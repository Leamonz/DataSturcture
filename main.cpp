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
#include "Sort.h"
#include <ctime>
#include <stack>
#include <iomanip>
#include "Schedule.h"
#include "Polynomial.h"

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
    else
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

//void InsertSort(int *arr, int n) {
//    for (int i = 1; i < n; i++) {
//        int elem = arr[i];
//        int j;
//        for (j = i - 1; j >= 0 && arr[j] > elem; j--) {
//            arr[j + 1] = arr[j];
//        }
//        arr[j + 1] = elem;
//    }
//}
//
//void ShellInsert(int *arr, int n, int incr) {
//    for (int i = incr; i < n; i += incr) {
//        int elem = arr[i];
//        int j;
//        for (j = i - incr; j >= 0 && arr[j] > elem; j -= incr) {
//            arr[j + incr] = arr[j];
//        }
//        arr[j + incr] = elem;
//    }
//}
//
//void ShellSort(int *arr, int n, int *inc, int t) {
//    for (int k = 0; k < t; k++) {
//        ShellInsert(arr, n, inc[k]);
//    }
//}
//
//void BubbleSort(int *arr, int n) {
//    for (int i = 0; i < n - 1; i++) {
//        for (int j = 0; j < n - i; j++) {
//            if (arr[j] > arr[j + 1]) {
//                int temp = arr[j + 1];
//                arr[j + 1] = arr[j];
//                arr[j] = temp;
//            }
//        }
//    }
//}
//
//void QuickSort(int *arr, int l, int r) {
//    if (l >= r) {
//        return;
//    }
//    int L = l, R = r;
//    int pivot = (l + r) / 2;
//    while (l < pivot && r > pivot) {
//        if (arr[l] > arr[pivot]) {
//            int temp = arr[pivot];
//            arr[pivot] = arr[l];
//            arr[l] = temp;
//        } else {
//            l++;
//        }
//        if (arr[r] < arr[pivot]) {
//            int temp = arr[pivot];
//            arr[pivot] = arr[r];
//            arr[r] = temp;
//        } else {
//            r--;
//        }
//    }
//    QuickSort(arr, L, pivot);
//    QuickSort(arr, pivot + 1, R);
//}
//
//void SelectSort(int *arr, int n) {
//    for (int i = 0; i < n; i++) {
//        int min = arr[i], min_pos = i;
//        for (int j = i + 1; j < n; j++) {
//            if (arr[j] < min) {
//                min_pos = j;
//            }
//        }
//        if (min_pos != i) {
//            int temp = arr[min_pos];
//            arr[min_pos] = arr[i];
//            arr[i] = temp;
//        }
//    }
//}
//
//void MergeSort(int *arr, int l, int r) {
//    if (l >= r)
//        return;
//    int mid = (l + r) / 2;
//    MergeSort(arr, l, mid);
//    MergeSort(arr, mid + 1, r);
//    int L = l, R = mid + 1;
//    int *brr = new int[r - l + 1], len = 0;
//    while (L <= mid && R <= r) {
//        if (arr[L] < arr[R]) {
//            brr[len++] = arr[L];
//            L++;
//        } else {
//            brr[len++] = arr[R];
//            R++;
//        }
//    }
//    while (L <= mid) {
//        brr[len++] = arr[L++];
//    }
//    while (R <= r) {
//        brr[len++] = arr[R++];
//    }
//    for (int i = l, j = 0; i <= r; i++, j++) {
//        arr[i] = brr[j];
//    }
//}

void CountingSort(int *arr, int n) {
    int *count = new int[n]{};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j != i) {
                count[i] += arr[i] > arr[j] ? 1 : 0;
            }
        }
    }
    int *brr = new int[n];
    for (int i = 0; i < n; i++) {
        brr[count[i]] = arr[i];
    }
    for (int i = 0; i < n; i++) {
        arr[i] = brr[i];
    }
    delete[] brr;
    delete[] count;
}

template<class ElemType>
bool isSortingTree(const BinaryTree<ElemType> &bt) {
    auto *r = bt.GetRoot();
    LinkQueue<BinTreeNode<ElemType> *> q;
    if (r == nullptr) {
        // 空树
        return false;
    }
    q.PushBack(r);
    while (!q.Empty()) {
        if (r->data < r->lChild->data || r->data > r->rChild->data) {
            // 不满足排序二叉树的定义， 即
            // 左子树的结点都小于根节点；右子树的结点都大于根节点
            return false;
        }
        if (r->lChild != nullptr) q.PushBack(r->lChild);
        if (r->rChild != nullptr) q.PushBack(r->rChild);
    }
    return true;
}

template<class ElemType>
void Insert(SimpleLinkList<ElemType> hashTable[], ElemType elem, int k) {
    // 首先模k取余得到哈希地址
    int pos = elem % k;
    // 然后将元素插入对应地址的链表的末尾
    // 如果该地址本身没有元素，则直接插入第一个
    // 如果该地址本身有元素，则在原有元素的末尾插入
    // 以上操作是相同的，即在链表的末尾插入元素
    hashTable[pos].Insert(hashTable[pos].Length() + 1, elem);
}

template<class ElemType>
void Difference(const SqList<ElemType> &la, const SqList<ElemType> &lb, SqList<ElemType> &lc) {
    ElemType aItem, bItem;
    bool isExist = false;
    for (int i = 1; i <= la.Length(); i++) {
        la.GetElem(i, aItem);
        for (int j = 1; j <= lb.Length(); j++) {
            lb.GetElem(j, bItem);
            if (aItem == bItem) {
                isExist = true;
                break;
            }
        }
        if (isExist) {
            isExist = false;
            continue;
        } else {
            lc.Insert(lc.Length() + 1, aItem);
        }
    }
}

void Adjust(SqList<int> &la) {
    int left = 1, right = la.Length(), lElem, rElem;
    la.GetElem(left, lElem);
    la.GetElem(right, rElem);
    while (left < right) {
        if (lElem % 2 == 1) {
            left++;
            la.GetElem(left, lElem);
        } else {
            while (rElem % 2 == 0 && right > left) {
                right--;
                la.GetElem(right, rElem);
            }
            if (right == left) {
                break;
            } else {
                int temp = rElem;
                la.SetElem(right, lElem);
                la.SetElem(left, temp);
                right--;
                left++;
                la.GetElem(right, rElem);
                la.GetElem(left, lElem);
            }
        }
    }
}

bool Match(const char *string) {
    LinkStack<char> stack;
    int len = strlen(string);
    char top;
    for (int i = 0; i < len; i++) {
        if (string[i] == '(' || string[i] == '[' || string[i] == '{') {
            stack.Push(string[i]);
        } else if (string[i] == ')') {
            if (!(stack.Top(top)) || top != '(') {
                return false;
            }
            stack.Pop();
        } else if (string[i] == ']') {
            if (!(stack.Top(top)) || top != '[') {
                return false;
            }
            stack.Pop();
        } else if (string[i] == '}') {
            if (!(stack.Top(top)) || top != '{') {
                return false;
            }
            stack.Pop();
        }
    }
    return stack.Empty();
}

void YangHuiTriangle(int n) {
    LinkQueue<int> queue;
    queue.PushBack(1);
    queue.PushBack(1);
    int s, t;
    for (int i = 1; i <= n; i++) {
        queue.PushBack(1);
        queue.PopFront(s);
        for (int j = 0; j < i; j++) {
            queue.PopFront(t);
            queue.PushBack(s + t);
            cout << s << ' ';
            s = t;
        }
        queue.PushBack(1);
        cout << s << endl;
    }
}

void InsertSort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int j;
        int e = arr[i];
        for (j = i - 1; j >= 0 && arr[j] > e; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = e;
    }
}

void ShellInsert(int *arr, int n, int incr) {
    for (int i = incr; i < n; i++) {
        int j = i - incr;
        int e = arr[i];
        for (; j >= 0 && arr[j] > e; j -= incr) {
            arr[j + incr] = arr[j];
        }
        arr[j + incr] = e;
    }
}

void ShellSort(int *arr, int n, int *incr, int t) {
    for (int k = 0; k < t; k++) {
        ShellInsert(arr, n, incr[k]);
    }
}

void BubbleSort(int *arr, int n) {
    bool swap = false;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
                swap = true;
            }
        }
        if (!swap)
            return;
    }
}

//void QuickSort(int *arr, int l, int r) {
//    if (l >= r)
//        return;
//    int pivot = (l + r) / 2;
//    for (int i = l; i < pivot; i++) {
//        if (arr[i] > arr[pivot]) {
//            int temp = arr[pivot];
//            arr[pivot] = arr[i];
//            arr[i] = temp;
//        }
//    }
//    for (int j = r; j > pivot; j--) {
//        if (arr[j] < arr[pivot]) {
//            int temp = arr[pivot];
//            arr[pivot] = arr[j];
//            arr[j] = temp;
//        }
//    }
//    for (int i = 0; i < 8; i++) {
//        cout << arr[i] << ' ';
//    }
//    cout << endl;
//    QuickSort(arr, l, pivot);
//    QuickSort(arr, pivot + 1, r);
//}

void SelectSort(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        int min_pos = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_pos]) {
                min_pos = j;
            }
        }
        if (i != min_pos) {
            int min = arr[min_pos];
            arr[min_pos] = arr[i];
            arr[i] = min;
        }
    }
}

void MergeSort(int *arr, int l, int r) {
    if (l >= r)
        return;
    int mid = (l + r) / 2;
    MergeSort(arr, l, mid);
    MergeSort(arr, mid + 1, r);
    int L = l, R = mid + 1, len = 0;
    int *brr = new int[r - l + 1];
    while (L <= mid && R <= r) {
        if (arr[L] < arr[R]) {
            brr[len++] = arr[L];
            L++;
        } else {
            brr[len++] = arr[R];
            R++;
        }
    }
    while (L <= mid) {
        brr[len++] = arr[L++];
    }
    while (R <= r) {
        brr[len++] = arr[R++];
    }
    for (int i = 0, j = l; j <= r; i++, j++) {
        arr[j] = brr[i];
    }
    delete[] brr;
}

#include <list>

int main() {
    list<int> l;
    for (int i = 0; i < 5; i++) {
        l.push_back(i);
        cout << i << ' ';
    }
    putchar('\n');
//    auto it = ++l.begin();
//    cout << *(l.erase(it)) << endl;
//    cout << *(l.erase(it)) << endl;
    for(int i:l) {
        cout << i << " ";
    }
    cout << endl;
    for(auto start = l.begin(); start!=l.end();) {
//        std::list<int>::iterator iter_e=start++;
        cout << *l.erase(start++) << " ";
//        start++;
    }
    cout << endl;

//    int arr[10] = {2, 5, 1, 7, 4, 6, 3, 8, 10, 9};
//    int brr[8] = {24, 19, 32, 43, 38, 6, 13, 22};
//    int inc[3] = {5, 3, 1};
////    MergeSort(arr, 0, 9);
//    QuickSort(brr, 0, 7);
//    for (int i: brr) {
//        cout << i << ' ';
//    }
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
//    bt.NonRecurInOrder(Print);
//    cout << endl;
//    cout << "非递归后序遍历" << endl;
//    bt.NonRecurPostOrder(Print);
//    cout << endl;

//    CharString s1("hello"), s2(" world");
//    s1 = s2;
//    CharString s3(s2);
//    cout << s1 << '\n' << s3 << endl;
//    Write(cout, s1);
//    Concat(s1, s2);
//    cout << s1 << endl;
//    s1 = Read(cin, ' ');
//    cout << s1;
//    YangHuiTriangle(10);
//    SqQueue<int> test1(5), test2;
//    test1.PushBack(1);
//    test1.PushBack(2);
//    test1.PushBack(3);
//    test1.PushBack(4);
//    test1.PopFront();
//    test1.PopFront();
//
//    test1.Traverse(Print);
//    cout << endl;
//    test2 = test1;
//    test2.Traverse(Print);
//    LinkQueue<int> test1, test2;
//    test1.PushBack(1);
//    test1.PushBack(2);
//    test1.PushBack(3);
//    test1.PushBack(4);
//    test1.PushBack(5);
//    int elem;
//    test1.Head(elem);
//    cout << elem << endl;
//    test1.PopFront();
//    test1.Head(elem);
//    cout << elem << endl;
//    test1.PopFront(elem);
//    cout << elem << endl;
//    test1.Traverse(Print);
//    cout << endl;
//    test2 = test1;
//    test2.Traverse(Print);
//    test1.Traverse(Print);
//    char *str = new char[255];
//    cin >> str;
//    if (Match(str)) {
//        cout << "YES" << endl;
//    } else {
//        cout << "NO" << endl;
//    }
//    LinkStack<double> test1;
//    double a = 3.3;
//    test1.Push(2);
//    test1.Push(2.5);
//    test1.Push(3.7);
//    test1.Push(9.9);
//    test1.Traverse(Triple);
//    test1.Traverse(Print);
//    Polynomial test1, test2;
//    test1.InsItem(Polyitem(1, 2));
//    test1.InsItem(Polyitem(-1, 3));
//    test1.InsItem(Polyitem(3, 4));
//    test1.InsItem(Polyitem(8, 7));
//    test2.InsItem(Polyitem(-1, 2));
//    test2.InsItem(Polyitem(3, 3));
//    test2.InsItem(Polyitem(2, 5));
//    test2.InsItem(Polyitem(-3, 4));
//    cout << test1 << endl;
//    cout << test2 << endl;
//    Polynomial test3;
//    test3 = test1 * test2;
//    cout << test3 << endl;
//    SimpleLinkList<int> list;
//    for (int i = 1; i <= 5; i++) {
//        list.Insert(list.Length() + 1, i);
//    }
//    list.Traverse(Print);
//    list.reverse();
//    list.Traverse(Print);
//    SqList<int> la, lb, lc;
//    la.Insert(la.Length() + 1, 3);
//    la.Insert(la.Length() + 1, 20);
//    la.Insert(la.Length() + 1, 19);
//    la.Insert(la.Length() + 1, 1);
//    la.Insert(la.Length() + 1, 6);
//    la.Insert(la.Length() + 1, 5);
//    la.Insert(la.Length() + 1, 4);
//    Adjust(la);
//    la.Traverse(Print);
//    lb.Insert(lb.Length() + 1, 3);
//    lb.Insert(lb.Length() + 1, 2);
//    lb.Insert(lb.Length() + 1, 14);
//    Difference(la, lb, lc);
//    lc.Traverse(Print);
//    BiLinkList<int> la;
//    la.Insert(la.Length() + 1, 4);
//    la.Insert(la.Length() + 1, 3);
//    la.Insert(la.Length() + 1, 1);
//    la.Insert(la.Length() + 1, 2);
//    la.Traverse(Print);
//    cout << endl;
//    BiLinkList<int> l2;
//    l2 = la;
//    l2.Traverse(Print);
//    auto tmpPtr = la.GetElemPtr(3);
//    if (tmpPtr == nullptr) {
//        cout << tmpPtr->data << endl;
//        cout << "nullptr" << endl;
//    } else {
//        cout << tmpPtr->data << endl;
//    }
    return 0;
}

//int main() {
//    char *inFile = new char[105], *outFile = new char[105];
//    cout << "请输入课表信息源文件: ";
//    cin >> inFile;
//    cout << "请输入排课结果保存文件: ";
//    cin >> outFile;
//    CharString in(inFile), out(outFile);
//    Schedule<8> schedule(in, out);
//    schedule.TopologicalOrder();
//    schedule.Write();
//
//
////    cout << setw(5) << "节次" << setw(10) << "星期一" << setw(10) << "星期二";
////    SimpleLinkList<int> hashTable[13];
////    Insert(hashTable, 19, 13);
////    Insert(hashTable, 14, 13);
////    Insert(hashTable, 23, 13);
////    Insert(hashTable, 1, 13);
////    Insert(hashTable, 68, 13);
////    Insert(hashTable, 20, 13);
////    Insert(hashTable, 84, 13);
////    Insert(hashTable, 27, 13);
////    Insert(hashTable, 55, 13);
////    Insert(hashTable, 11, 13);
////    Insert(hashTable, 10, 13);
////    Insert(hashTable, 79, 13);
////    for (int i = 0; i < 13; i++) {
////        cout << i << ": ";
////        for (int j = 1; j <= hashTable[i].Length(); j++) {
////            int elem = hashTable[i].GetElem(j);
////            cout << elem << ' ';
////        }
////        cout << endl;
////    }
////    char *pre = "CBADEGFH";
////    char *in = "ABCEFGHD";
////    BinaryTree<char> bt = CreateBinaryTree(pre, in, 8);
////    DisplayBTWithTreeShape(bt);
////
////    int arr[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
////    InsertSort(arr, 10);
////    int inc[3] = {1, 2, 4};
////    ShellSort(arr, 10, inc, 3);
////    BubbleSort(arr, 10);
////    QuickSort(arr, 0, 9);
////    SelectSort(arr, 10);
////    int brr[10] = {40, 55, 49, 73, 12, 27, 98, 81, 64, 36};
////    Sift(brr, 10);
////    HeapSort(brr, 10);
////    MergeSort(arr, 0, 9);
////    CountingSort(arr, 10);
////    for (int i: arr) {
////        cout << i << ' ';
////    }
//
//
////    int n, i, j;
////    cin >> n;
////    int mat[n][n];
////    //创建两个数组分别用于存储每一行最小值的列下标以及每一列最大值的行下标
////    int rows_min[n], cols_max[n];
////    for (i = 0; i < n; i++) {
////        // 初始化两个辅助数组
////        rows_min[i] = cols_max[i] = 0;
////    }
////    for (i = 0; i < n; i++) {
////        for (j = 0; j < n; j++) {
////            cin >> mat[i][j];
////            if (mat[i][j] < mat[i][rows_min[i]]) {
////                rows_min[i] = j;
////            }
////            if (mat[i][j] > mat[cols_max[j]][j]) {
////                cols_max[j] = i;
////            }
////        }
////    }
////    pair<int, int> dots[n];
////    int cnt = 0;
////    for (i = 0; i < n; i++) {
////        for (j = 0; j < n; j++) {
////            // 遍历矩阵寻找符合条件的点
////            // A[i][j]恰好是第i行的最小值，恰好是第j列的最大值
////            if (rows_min[i] == j && cols_max[j] == i) {
////                dots[cnt++] = make_pair(i, j);
////            }
////        }
////    }
////    for (int k = 0; k < cnt; k++) {
////        cout << "(" << dots[k].first << ", " << dots[k].second << ")" << " " << mat[dots[k].first][dots[k].second]
////             << endl;
////    }
//
////    clock_t startRecur = clock();
////    cout << Akm(3, 10) << endl;
////    clock_t endRecur = clock();
////    cout << "Recursive: " << (double) (endRecur - startRecur) / CLOCKS_PER_SEC << "s" << endl;
////    clock_t startNonRecur = clock();
////    cout << NonRecurAkm(3, 10) << endl;
////    clock_t endNonRecur = clock();
////    cout << "NonRecursive: " << (double) (endNonRecur - startNonRecur) / CLOCKS_PER_SEC << "s" << endl;
////    SimpleLinkList<int> la, lb, lc;
////    la.Insert(la.Length() + 1, 3);
////    la.Insert(la.Length() + 1, 5);
////    la.Insert(la.Length() + 1, 9);
////    lb.Insert(lb.Length() + 1, 2);
////    lb.Insert(lb.Length() + 1, 4);
////    lb.Insert(lb.Length() + 1, 8);
////    lb.Insert(lb.Length() + 1, 10);
////    lb.Insert(lb.Length() + 1, 20);
////    la.Traverse(Print);
////    cout << endl;
////    lb.Traverse(Print);
////    cout << endl;
////    Merge(la, lb, lc);
////    lc.Traverse(Print);
////    char pre[] = "ABCDEFGHI";
////    char in[] = "DCBAGFHEI";
////    BinaryTree<char> bt = CreateBinaryTree(pre, in, strlen(pre));
////    cout << "递归先序遍历" << endl;
////    bt.PreOrder(Print);
////    cout << endl;
////    cout << "递归中序遍历" << endl;
////    bt.InOrder(Print);
////    cout << endl;
////    cout << "递归后续遍历" << endl;
////    bt.PostOrder(Print);
////    cout << endl;
////    cout << "非递归先序遍历" << endl;
////    bt.NonRecurPreOrder(Print);
////    cout << endl;
////    cout << "非递归中序遍历" << endl;
//////    bt.NonRecurInOrder(Print);
////    cout << endl;
////    cout << "非递归后序遍历" << endl;
//////    bt.NonRecurPostOrder(Print);
////    cout << endl;
//
//
////    ifstream inf;
////    inf.open("test.txt", ios::binary | ios::in);
////    char ch;
////    int size = 1;
////    inf.read(&ch, sizeof(char));
////    putchar(ch);
////    while (!inf.eof()) {
////        inf.read(&ch, sizeof(char));
////        if (inf.eof()) break;
////        putchar(ch);
////    }
////    if (inf.eof()) {
////        cout << "hhh" << endl;
////    }
////    inf.clear();
////    inf.seekg(0, ios::beg);
//
////    while (!inf.eof()) {
////        inf.read(&ch, sizeof(char));
////        putchar(ch);
////    }
//
////    HuffmanCompress huffmanCompress;
////    bool active = true;
////    while (active) {
////        active = huffmanCompress.Run();
////    }
////    char ch[4] = {'a', 'b', 'c', 'd'};
////    unsigned long w[4] = {9, 8, 1, 6};
////    HuffmanTree<char, unsigned long> test(ch, w, 4);
////    CharString code = test.Encode('b');
////    cout << code;
////    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
////    int pos = RecurBinSearch(arr, 0, 9, 3);
////    cout << pos << ": " << arr[pos] << endl;
////    int a, b, c;
////    cin >> a >> b >> c;
////    cout << "Max: " << Max(a, b, c) << endl;
//    return 0;
//}