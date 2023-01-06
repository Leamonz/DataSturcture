//
// Created by HP on 2022/10/1.
//

#ifndef UTILS_HPP_BINARYTREE_H
#define UTILS_HPP_BINARYTREE_H

#include<iostream>
#include "MyQueue.h"

using namespace std;

//链式存储结构的二叉树
template<class ElemType>
struct BinTreeNode {
    ElemType data;
    BinTreeNode<ElemType> *lChild;
    BinTreeNode<ElemType> *rChild;

    BinTreeNode() {
        lChild = NULL;
        rChild = NULL;
        data = 0;
    }

    explicit BinTreeNode(ElemType d, BinTreeNode<ElemType> *l = NULL, BinTreeNode<ElemType> *r = NULL) {
        data = d;
        lChild = l;
        rChild = r;
    }
};

template<class ElemType>
class BinaryTree {
protected:
// 数据成员:
    BinTreeNode<ElemType> *root;

// 辅助函数模板:
    BinTreeNode<ElemType> *CopyTreeHelp(const BinTreeNode<ElemType> *r);// 复制二叉树
    void DestroyHelp(BinTreeNode<ElemType> *&r);                        // 销毁以r为根二叉树
    void PreOrderHelp(BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const;    // 先序遍历
    void InOrderHelp(BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const;    // 中序遍历
    void PostOrderHelp(BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const;// 后序遍历
    int HeightHelp(const BinTreeNode<ElemType> *r) const;    // 返回二叉树的高
    int NodeCountHelp(const BinTreeNode<ElemType> *r) const;// 返回二叉树的结点个数


    const BinTreeNode<ElemType> *ParentHelp(BinTreeNode<ElemType> *r,
                                            const BinTreeNode<ElemType> *cur) const;            // 返回cur的双亲

public:
// 二叉树方法声明及重载编译系统默认方法声明:
    BinaryTree();                                            // 无参数的构造函数模板
    virtual ~BinaryTree();                                    // 析构函数
    const BinTreeNode<ElemType> *GetRoot() const;            // 返回二叉树的根
    bool Empty() const;                                        // 判断二叉树是否为空
    bool GetElem(const BinTreeNode<ElemType> *cur, ElemType &e) const;    // 用e返回结点元素值
    bool SetElem(BinTreeNode<ElemType> *cur, const ElemType &e);    // 将结点cur的值置为e
    void InOrder(void (*visit)(const ElemType &)) const;    // 二叉树的中序遍历
    void NonRecurInOrder(void(*visit)(const ElemType &)) const; //非递归中序遍历

    void PreOrder(void (*visit)(const ElemType &)) const;    // 二叉树的先序遍历
    void NonRecurPreOrder(void(*visit)(const ElemType &)) const; //非递归先序遍历

    void PostOrder(void (*visit)(const ElemType &)) const;    // 二叉树的后序遍历
    void NonRecurPostOrder(void(*visit)(const ElemType &)) const; //非递归后序遍历
    void LevelOrder(void (*visit)(const ElemType &)) const;    // 二叉树的层次遍历
    int NodeCount() const;                                    // 求二叉树的结点个数
    const BinTreeNode<ElemType> *LeftChild(const BinTreeNode<ElemType> *cur) const;

    // 返回二叉树结点cur的左孩子
    const BinTreeNode<ElemType> *RightChild(const BinTreeNode<ElemType> *cur) const;

    // 返回二叉树结点cur的右孩子
    const BinTreeNode<ElemType> *Parent(const BinTreeNode<ElemType> *cur) const;

    // 返回二叉树结点cur的双亲
    void InsertLeftChild(BinTreeNode<ElemType> *cur, const ElemType &e);// 插入左孩子
    void InsertRightChild(BinTreeNode<ElemType> *cur, const ElemType &e);// 插入右孩子
    void DeleteLeftChild(BinTreeNode<ElemType> *cur);        // 删除左子树
    void DeleteRightChild(BinTreeNode<ElemType> *cur);        // 删除右子村



    int Height() const;                                        // 求二叉树的高
    explicit BinaryTree(const ElemType &e);                            // 建立以e为根的二叉树
    BinaryTree(const BinaryTree<ElemType> &source);            // 复制构造函数模板
    explicit BinaryTree(BinTreeNode<ElemType> *r);                    // 建立以r为根的二叉树
    BinaryTree<ElemType> &operator=(const BinaryTree<ElemType> &source);    // 重载赋值运算符
};


template<class ElemType>
BinaryTree<ElemType>::BinaryTree() {
    root = NULL;
}

template<class ElemType>
bool BinaryTree<ElemType>::Empty() const {
    return root == NULL;
}

template<class ElemType>
const BinTreeNode<ElemType> *BinaryTree<ElemType>::GetRoot() const {
    return root;
}


template<class ElemType>
BinaryTree<ElemType>::BinaryTree(const ElemType &e) {
    root = new BinTreeNode<ElemType>(e);
}

template<class ElemType>
BinaryTree<ElemType>::BinaryTree(BinTreeNode<ElemType> *r) {
    root = CopyTreeHelp(r);
}

template<class ElemType>
BinaryTree<ElemType>::BinaryTree(const BinaryTree<ElemType> &source) {
    root = CopyTreeHelp(source.root);
}

//递归描述二叉树的遍历
//二叉树先序遍历
template<class ElemType>
void BinaryTree<ElemType>::PreOrderHelp(BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const {
    if (r != NULL) {
        visit(r->data);//遍历根节点
        PreOrderHelp(r->lChild, visit);//遍历左子树
        PreOrderHelp(r->rChild, visit);//遍历右子树
    }
}

template<class ElemType>
void BinaryTree<ElemType>::PreOrder(void (*visit)(const ElemType &)) const {
    PreOrderHelp(root, visit);
}

//二叉树中序遍历
template<class ElemType>
void BinaryTree<ElemType>::InOrderHelp(BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const {
    if (r != NULL) {
        InOrderHelp(r->lChild, visit);//遍历左子树
        visit(r->data);//遍历根节点
        InOrderHelp(r->rChild, visit);//遍历右子树
    }
}

template<class ElemType>
void BinaryTree<ElemType>::InOrder(void (*visit)(const ElemType &)) const {
    InOrderHelp(root, visit);
}

//二叉树后序遍历
template<class ElemType>
void BinaryTree<ElemType>::PostOrderHelp(BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const {
    if (r != NULL) {
        PostOrderHelp(r->lChild, visit);//遍历左子树
        PostOrderHelp(r->rChild, visit);//遍历右子树
        visit(r->data);//遍历根节点
    }
}

template<class ElemType>
void BinaryTree<ElemType>::PostOrder(void (*visit)(const ElemType &)) const {
    PostOrderHelp(root, visit);
}

//二叉树遍历应用
//求二叉树中结点个数   左子树结点 + 右子树结点 + 1
template<class ElemType>
int BinaryTree<ElemType>::NodeCountHelp(const BinTreeNode<ElemType> *r) const {
    if (r != NULL) {
        return NodeCountHelp(r->lChild) + NodeCountHelp(r->rChild) + 1;
    }
    return 0;
}

template<class ElemType>
int BinaryTree<ElemType>::NodeCount() const {
    return NodeCountHelp(root);
}

//求二叉树的高度
template<class ElemType>
int BinaryTree<ElemType>::HeightHelp(const BinTreeNode<ElemType> *r) const {
    if (r != NULL) {
        return max(HeightHelp(r->lChild), HeightHelp(r->rChild)) + 1;
    }
    return 0;
}

template<class ElemType>
int BinaryTree<ElemType>::Height() const {
    return HeightHelp(root);
}

//二叉树的销毁
template<class ElemType>
void BinaryTree<ElemType>::DestroyHelp(BinTreeNode<ElemType> *&r) {
    if (r != NULL) {
        DestroyHelp(r->lChild);
        DestroyHelp(r->rChild);
        delete r;
        r = NULL;
    }
}

template<class ElemType>
BinaryTree<ElemType>::~BinaryTree() {
    DestroyHelp(root);
}

//二叉树的复制
template<class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::CopyTreeHelp(const BinTreeNode<ElemType> *r) {
    if (r != NULL) {
        BinTreeNode<ElemType> *lChild = CopyTreeHelp(r->lChild);//复制左子树
        BinTreeNode<ElemType> *rChild = CopyTreeHelp(r->rChild);//复制右子树
        auto *res = new BinTreeNode<ElemType>(r->data, lChild, rChild);//复制根节点
        return res;
    } else {
        return NULL;
    }
}

template<class ElemType>
BinaryTree<ElemType> &BinaryTree<ElemType>::operator=(const BinaryTree<ElemType> &source) {
    if (&source != this) {
        DestroyHelp(root);
        root = CopyTreeHelp(source.root);
    }
    return *this;
}

//树状显示二叉树
template<class ElemType>
void DisplayBTWithTreeShapeHelp(const BinTreeNode<ElemType> *r, int level) {
    if (r != NULL) {
        //显示右子树
        DisplayBTWithTreeShapeHelp(r->rChild, level + 1);
        cout << endl;
        for (int i = 0; i < level - 1; i++) {
            cout << " ";
        }   //level表示列
        cout << r->data;
        //显示左子树
        DisplayBTWithTreeShapeHelp(r->lChild, level + 1);
    }
}

template<class ElemType>
void DisplayBTWithTreeShape(BinaryTree<ElemType> &bt) {
    DisplayBTWithTreeShapeHelp(bt.GetRoot(), 1);
    cout << endl;
}

template<class ElemType>
void BinaryTree<ElemType>::LevelOrder(void (*visit)(const ElemType &)) const {
    LinkQueue<BinTreeNode<ElemType> *> q;
    if (root == nullptr) return;//空树
    visit(root->data);
    if (root->lChild != nullptr) q.PushBack(root->lChild);
    if (root->rChild != nullptr) q.PushBack(root->rChild);
    while (!q.Empty()) {
        BinTreeNode<ElemType> *tmp = q.PopFront();
        visit(tmp->data);
        if (tmp->lChild != nullptr) q.PushBack(tmp->lChild);
        if (tmp->rChild != nullptr) q.PushBack(tmp->rChild);
    }
}

template<class ElemType>
const BinTreeNode<ElemType> *BinaryTree<ElemType>::LeftChild(const BinTreeNode<ElemType> *cur) const {
    return cur->lChild;
}

template<class ElemType>
const BinTreeNode<ElemType> *BinaryTree<ElemType>::RightChild(const BinTreeNode<ElemType> *cur) const {
    return cur->rChild;
}

template<class ElemType>
void BinaryTree<ElemType>::InsertLeftChild(BinTreeNode<ElemType> *cur, const ElemType &e) {
    auto *newNode = new BinTreeNode<ElemType>(e, cur->lChild);
    cur->lChild = newNode;
}

template<class ElemType>
void BinaryTree<ElemType>::InsertRightChild(BinTreeNode<ElemType> *cur, const ElemType &e) {
    auto *newNode = new BinTreeNode<ElemType>(e, NULL, cur->rChild);
    cur->rChild = newNode;
}

template<class ElemType>
bool BinaryTree<ElemType>::GetElem(const BinTreeNode<ElemType> *cur, ElemType &e) const {
    if (cur != nullptr) {
        e = cur->data;
        return true;
    } else {
        return false;
    }
}

template<class ElemType>
bool BinaryTree<ElemType>::SetElem(BinTreeNode<ElemType> *cur, const ElemType &e) {
    if (cur != nullptr) {
        cur->data = e;
        return true;
    } else {
        return false;
    }
}

template<class ElemType>
const BinTreeNode<ElemType> *
BinaryTree<ElemType>::ParentHelp(BinTreeNode<ElemType> *r, const BinTreeNode<ElemType> *cur) const {
    LinkQueue<BinTreeNode<ElemType> *> q;
    if (r->lChild == cur || r->rChild == cur) return r;
    q.PushBack(r->lChild);
    q.PushBack(r->rChild);
    while (!q.Empty()) {
        auto tmp = q.PopFront();
        if (tmp->rChild == cur || tmp->lChild == cur) return tmp;
        q.PushBack(tmp->lChild);
        q.PushBack(tmp->rChild);
    }
    return nullptr;
}

template<class ElemType>
const BinTreeNode<ElemType> *BinaryTree<ElemType>::Parent(const BinTreeNode<ElemType> *cur) const {
    if (root != nullptr)
        return ParentHelp(root, cur);
    else
        return nullptr;//空树
}

template<class ElemType>
void BinaryTree<ElemType>::DeleteLeftChild(BinTreeNode<ElemType> *cur) {
    if (cur->lChild != nullptr)
        delete cur->lChild;
}

template<class ElemType>
void BinaryTree<ElemType>::DeleteRightChild(BinTreeNode<ElemType> *cur) {
    if (cur->rChild != nullptr)
        delete cur->rChild;
}

template<class ElemType>
void BinaryTree<ElemType>::NonRecurInOrder(void (*visit)(const ElemType &)) const {

}

template<class ElemType>
void BinaryTree<ElemType>::NonRecurPreOrder(void (*visit)(const ElemType &)) const {
    LinkStack<BinTreeNode<ElemType> *> s;
    if (root == nullptr) return;//空树
    visit(root->data);
    if (root->rChild != nullptr) s.Push(root->rChild);
    BinTreeNode<ElemType> *tmp = root->lChild;
    while (true) {
        while (tmp != nullptr) {
            visit(tmp->data);
            if (tmp->rChild != nullptr) s.Push(tmp->rChild);
            tmp = tmp->lChild;
        }
        if (s.Empty()) break;
        tmp = s.Pop();
    }
}

//已知前序序列和中序序列构造二叉树
/*
 * 操作结果：已知二叉树的先序序列 pre[preLeft, ..., preRight]和中序序列 in[inLeft, ..., inRight]构造以r为根的二叉树
 * params:
 * r: root pointer
 * pre[]: preorder array
 * in[]: inorder array
 *
 **/
template<class ElemType>
void CreateBinaryTreeHelp(BinTreeNode<ElemType> *&r, ElemType pre[], ElemType in[], int preLeft, int preRight,
                          int inLeft, int inRight) {
    if (inLeft > inRight) {
        //创造空树
        r = NULL;
    } else {
        r = new BinTreeNode<ElemType>(pre[preLeft]);//找到根节点
        int mid = inLeft;
        while (in[mid] != pre[preLeft]) {
            mid++;//找到中序序列中根节点所在位置
        }
        //构造左子树
        CreateBinaryTreeHelp(r->lChild, pre, in, preLeft + 1, preLeft + mid - inLeft,
                             inLeft, mid - 1);
        //构造右子树
        CreateBinaryTreeHelp(r->rChild, pre, in, preLeft + mid - inLeft + 1, preRight,
                             mid + 1, inRight);
    }
}

template<class ElemType>
BinaryTree<ElemType> &CreateBinaryTree(ElemType pre[], ElemType in[], unsigned int n) {
    /*
     * pre[]: preorder array
     * in[]: inorder array
     * n: number of nodes
     * */
    auto *r = new BinTreeNode<ElemType>;
    CreateBinaryTreeHelp(r, pre, in, 0, n - 1, 0, n - 1);
    auto *bt = new BinaryTree<ElemType>(r);
    return *bt;
}


#endif //UTILS_HPP_BINARYTREE_H
