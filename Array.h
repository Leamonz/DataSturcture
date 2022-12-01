//
// Created by HP on 2022/9/24.
//

#ifndef UTILS_HPP_ARRAY_H
#define UTILS_HPP_ARRAY_H

#include<iostream>
#include<cstdarg>

using namespace std;

//行优先映射
template<class ElemType>
class Array {
protected:
    ElemType *base;//数组元素基地址
    int dim;//维数
    int *bounds;//数组各维度的长度
    int *constant;//数组映像函数常量

    int Locate(int sub0, va_list &va) const;//求元素在顺序存储中的位置
public:
    Array(int d, ...);//由维数d和各维度长度构造数组
    ~Array();

    ElemType &operator()(int sub0, ...);//重载函数运算符用于访问数组中的元素
    Array(const Array<ElemType> &copy);

    Array<ElemType> &operator=(const Array<ElemType> &copy);
};

template<class ElemType>
Array<ElemType>::Array(int d, ...) {
    dim = d;
    bounds = new int[dim];
    int total = 1;
    va_list args;
    va_start(args, d);
    for (int i = 0; i < dim; i++) {
        bounds[i] = va_arg(args, int);
        total *= bounds[i];
    }
    va_end(args);
    base = new ElemType[total];
    if (base == NULL) {
        cout << "动态内存不足" << endl;
    }
    constant = new int[dim];
    constant[dim - 1] = 1;
    for (int i = dim - 2; i >= 0; i--) {
        constant[i] = constant[i + 1] * bounds[i + 1];
    }
}

//sub0为第一维度对应下标
template<class ElemType>
int Array<ElemType>::Locate(int sub0, va_list &va) const {
    int position = constant[0] * sub0;
    for (int i = 1; i < dim; i++) {
        int sub = va_arg(va, int);
        position += constant[i] * sub;
    }
    return position;
}

template<class ElemType>
ElemType &Array<ElemType>::operator()(int sub0, ...) {
    va_list args;
    va_start(args, sub0);
    int position = Locate(sub0, args);
    va_end(args);
    return base[position];
}

template<class ElemType>
Array<ElemType>::Array(const Array<ElemType> &copy) {
    this->dim = copy.dim;
    bounds = new int[dim];
    constant = new int[dim];
    int total = 1;
    for (int i = 0; i < dim; i++) {
        bounds[i] = copy.bounds[i];
        constant[i] = copy.constant[i];
        total *= bounds[i];
    }
    base = new int[total];
    for (int i = 0; i < total; i++) {
        base[i] = copy.base[i];
    }
}

template<class ElemType>
Array<ElemType> &Array<ElemType>::operator=(const Array<ElemType> &copy) {
    if (&copy != this) {
        if (bounds != NULL) {
            delete[] bounds;
        }
        if (constant != NULL) {
            delete[] constant;
        }
        if (base != NULL) {
            delete[] base;
        }
        this->dim = copy.dim;
        bounds = new int[dim];
        constant = new int[dim];
        int total = 1;
        for (int i = 0; i < dim; i++) {
            bounds[i] = copy.bounds[i];
            constant[i] = copy.constant[i];
            total *= bounds[i];
        }
        base = new int[total];
        for (int i = 0; i < total; i++) {
            base[i] = copy.base[i];
        }
    }
    return *this;
}

template<class ElemType>
Array<ElemType>::~Array() {
    if (bounds != NULL) {
        delete[] bounds;
    }
    if (constant != NULL) {
        delete[] constant;
    }
    if (base != NULL) {
        delete[] base;
    }
}

#endif //UTILS_HPP_ARRAY_H
