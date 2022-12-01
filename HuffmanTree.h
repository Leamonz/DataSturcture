//
// Created by HP on 2022/11/28.
//

#ifndef UNTITLED_HUFFMANTREE_H
#define UNTITLED_HUFFMANTREE_H

#include "MyString.h"
#include "MyList.h"
#include <iostream>

using namespace std;

template<class WeightType>
struct HuffmanTreeNode {
    WeightType weight;
    unsigned int parent, lChild, rChild;

    HuffmanTreeNode();

    explicit HuffmanTreeNode(WeightType w, int p = 0, int l = 0, int r = 0);
};

template<class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode() {
    weight = 0;
    parent = lChild = rChild = 0;
}

template<class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode(WeightType w, int p, int l, int r) {
    weight = w;
    parent = p;
    lChild = l;
    rChild = r;
}

template<class CharType, class WeightType>
class HuffmanTree {
protected:
    HuffmanTreeNode<WeightType> *nodes;//存储结点信息，nodes[0]未用
    CharType *LeafChars;//叶结点字符信息
    CharString *LeafCharCodes;//叶结点字符编码信息
    int curPos;//译码时从根节点到叶结点路径的当前结点
    int num; //叶结点个数

    void Select(int cur, int &r1, int &r2);//从nodes[1~cur]中选出权值最小的两个结点
    void CreateHuffmanTree(CharType ch[], WeightType w[], unsigned int n);

public:
    HuffmanTree(CharType ch[], WeightType w[], unsigned int n);

    virtual ~HuffmanTree();

    CharString Encode(CharType ch);

    CharString Decode(const CharString &code);

};

template<class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::Select(int cur, int &r1, int &r2) {
    int temp;
    for (int i = 1; i <= cur; i++) {
        if (nodes[i].parent != 0)
            continue;
        if (nodes[i].weight < nodes[r1].weight) {
            temp = r1;
            r1 = i;
        } else if (nodes[i].weight < nodes[r2].weight) {
            r2 = i;
        }
        if (nodes[temp].weight < nodes[r2].weight) {
            r2 = temp;
        }
    }
}

template<class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::CreateHuffmanTree(CharType *ch, WeightType *w, unsigned int n) {
    this->num = n;//叶结点个数 n
    int m = 2 * n - 1;
    LeafChars = new CharType[n + 1];
    LeafCharCodes = new CharString[n + 1];
    nodes = new HuffmanTreeNode<WeightType>[m + 1];//结点个数2n-1
    nodes[0].weight = (WeightType) 1e8;
    for (int i = 1; i <= n; i++) {
        LeafChars[i] = ch[i - 1];
        nodes[i].weight = w[i - 1];
    }
    for (unsigned int pos = n + 1; pos <= m; pos++) {
        int r1 = 0, r2 = 0;
        Select(pos - 1, r1, r2);
        nodes[r1].parent = pos;
        nodes[r2].parent = pos;
        nodes[pos].lChild = r1;
        nodes[pos].rChild = r2;
        nodes[pos].weight = nodes[r1].weight + nodes[r2].weight;
    }
    for (unsigned int i = 1; i <= n; i++) {
        SimpleLinkList<CharType> charCode;
        for (unsigned int child = i, parent = nodes[child].parent;
             parent != 0;
             child = parent, parent = nodes[child].parent) {
            if (nodes[parent].lChild == child) charCode.Insert(1, '0');
            else charCode.Insert(1, '1');
        }
        LeafCharCodes[i] = charCode;
    }
    curPos = m;//根节点位置
}

template<class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree(CharType *ch, WeightType *w, unsigned int n) {
    CreateHuffmanTree(ch, w, n);
}

template<class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::~HuffmanTree() {
    delete[] nodes;
    delete[] LeafChars;
    delete[] LeafCharCodes;
}

template<class CharType, class WeightType>
CharString HuffmanTree<CharType, WeightType>::Encode(CharType ch) {
    CharString code;
    unsigned int child = 0, parent = 0;
    // 找到ch对应叶结点位置
    for (unsigned int i = 1; i <= num; i++) {
        if (LeafChars[i] == ch) {
            return LeafCharCodes[i];
        }
    }
    cerr << "CAN'T DECODE THIS CHAR" << endl;
    return CharString("CAN'T DECODE THIS CHAR");
}

template<class CharType, class WeightType>
CharString HuffmanTree<CharType, WeightType>::Decode(const CharString &code) {
    SimpleLinkList<CharType> ListOfChars;
    int len = 0;
    int i = code.Length();
    for (unsigned int pos = 0; pos < code.Length(); pos++) {
        if (code[pos] == '0') {
            curPos = nodes[curPos].lChild;
        } else {
            curPos = nodes[curPos].rChild;
        }
        if (nodes[curPos].lChild == 0 && nodes[curPos].rChild == 0) {
            ListOfChars.Insert(ListOfChars.Length() + 1, LeafChars[curPos]);
            curPos = 2 * num - 1;
        }
    }
    return CharString(ListOfChars);
}


#endif //UNTITLED_HUFFMANTREE_H
