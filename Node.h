//
// Created by HP on 2022/9/16.
//

#ifndef CLION_NODE_H
#define CLION_NODE_H

#include<iostream>

template<class ElemType>
struct Node {
    ElemType data{};
    Node<ElemType> *next;

    Node() {
        next = nullptr;
    }

    explicit Node(ElemType data, Node<ElemType> *n = nullptr) {
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
    ElemType data{};
    DblNode<ElemType> *prev;
    DblNode<ElemType> *next;

    DblNode() {
        prev = nullptr;
        next = nullptr;
    }

    explicit DblNode(ElemType data, DblNode<ElemType> *p = nullptr, DblNode<ElemType> *n = nullptr) {
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
