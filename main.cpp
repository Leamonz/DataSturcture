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

using namespace std;

void Print(const char &ch) {
    cout << ch << ' ';
}

int main() {
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

    HuffmanCompress huffmanCompress;
    bool active = true;
    while (active) {
        active = huffmanCompress.Run();
    }
//    char ch[4] = {'a', 'b', 'c', 'd'};
//    unsigned long w[4] = {9, 8, 1, 6};
//    HuffmanTree<char, unsigned long> test(ch, w, 4);
//    CharString code = test.Encode('b');
//    cout << code;
    return 0;
}