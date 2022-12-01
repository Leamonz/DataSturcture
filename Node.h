//
// Created by HP on 2022/9/16.
//

#ifndef CLION_NODE_H
#define CLION_NODE_H

#include<iostream>

template<class ElemType>
struct Node {
    ElemType data;
    Node<ElemType> *next;

    Node() {
        data = 0;
        next = NULL;
    }

    Node(ElemType data, Node<ElemType> *n) {
        this->data = data;
        next = n;
    }

    Node(const Node<ElemType> &copy) {
        this->data = copy.data;
        this->next = copy.next;
    }
};

template<class ElemType>
struct DblNode {
    ElemType data;
    DblNode<ElemType> *prev;
    DblNode<ElemType> *next;

    DblNode() {
        data = 0;
        prev = NULL;
        next = NULL;
    }

    DblNode(ElemType data, DblNode<ElemType> *p, DblNode<ElemType> *n) {
        this->data = data;
        prev = p;
        next = n;
    }

    DblNode(const DblNode<ElemType> &copy) {
        this->data = copy.data;
        this->next = copy.next;
        this->prev = copy.prev;
    }
};


#endif //CLION_NODE_H
