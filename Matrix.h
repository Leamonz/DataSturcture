//
// Created by HP on 2022/9/25.
//

#ifndef UTILS_HPP_MATRIX_H
#define UTILS_HPP_MATRIX_H

#include<iostream>

using namespace std;

template<class ElemType>
class Matrix {
protected:
    ElemType *elems;
    // pair的两个元素分别用来储存行和列
    pair<int, int> shape;
public:
    explicit Matrix(int r = 10, int c = 10);

    ~Matrix();

    int GetRows() const {
        return shape.first;
    }

    int GetCols() const {
        return shape.second;
    }

    ElemType &operator()(int i, int j) const;

    Matrix(const Matrix<ElemType> &copy);

    Matrix<ElemType> &operator=(const Matrix<ElemType> &copy);
};


template<class ElemType>
Matrix<ElemType>::Matrix(int r, int c) {
    shape = make_pair(r, c);
    int rows = shape.first;
    int cols = shape.second;
    elems = new ElemType[rows * cols];
}

template<class ElemType>
Matrix<ElemType>::Matrix(const Matrix<ElemType> &copy) {
    this->shape = copy.shape;
    int rows = shape.first;
    int cols = shape.second;
    elems = new ElemType[rows * cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int off = i * cols + j;
            elems[off] = copy.elems[off];
        }
    }
}

template<class ElemType>
Matrix<ElemType> &Matrix<ElemType>::operator=(const Matrix<ElemType> &copy) {
    if (&copy != this) {
        if (elems != NULL) {
            delete[] elems;
        }
        this->shape = copy.shape;
        int rows = shape.first, cols = shape.second;
        elems = new ElemType[rows * cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int off = i * cols + j;
                elems[off] = copy.elems[off];
            }
        }
    }
    return *this;
}

template<class ElemType>
Matrix<ElemType>::~Matrix() {
    if (elems != NULL) {
        delete[] elems;
    }
}

template<class ElemType>
ElemType &Matrix<ElemType>::operator()(int i, int j) const {
    int off = i * shape.second + j;
    return elems[off];
}

template<class ElemType>
Matrix<ElemType> operator+(const Matrix<ElemType> &mat1, const Matrix<ElemType> &mat2) {
    Matrix<ElemType> ans(mat1.shape.first, mat1.shape.second);
    if (mat1.shape != mat2.shape) {
        cout << "Can't add matrices with shape " << "(" << mat1.shape.first << "," << mat1.shape.second << ") ";
        cout << "and (" << mat2.shape.first << "," << mat2.shape.second << ").";
        exit(1);
    } else {
        int rows = mat1.shape.first, cols = mat1.shape.second;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                ans(i, j) = mat1(i, j) + mat2(i, j);
            }
        }
    }
    return ans;
}

template<class ElemType>
Matrix<ElemType> operator-(const Matrix<ElemType> &mat1, const Matrix<ElemType> &mat2) {
    Matrix<ElemType> ans(mat1.shape.first, mat1.shape.second);
    if (mat1.shape != mat2.shape) {
        cout << "Can't subtract matrices with shape " << "(" << mat1.shape.first << "," << mat1.shape.second << ") ";
        cout << "and (" << mat2.shape.first << "," << mat2.shape.second << ").";
        exit(1);
    } else {
        int rows = mat1.shape.first, cols = mat1.shape.second;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                ans(i, j) = mat1(i, j) - mat2(i, j);
            }
        }
    }
    return ans;
}

template<class ElemType>
Matrix<ElemType> operator*(const Matrix<ElemType> &mat1, const Matrix<ElemType> &mat2) {
    Matrix<ElemType> ans(mat1.shape.first, mat2.shape.second);
    if (mat1.shape.second != mat2.shape.first) {
        cout << "Can't multiply matrices with shape " << "(" << mat1.shape.first << "," << mat1.shape.second << ") ";
        cout << "and (" << mat2.shape.first << "," << mat2.shape.second << ").";
        exit(1);
    } else {
        for (int i = 0; i < mat1.shape.first; i++) {
            for (int j = 0; j < mat2.shape.second; j++) {
                int sum = 0;
                for (int k = 0; k < mat1.shape.second; k++) {
                    sum += mat1(i, k) * mat2(k, j);
                }
                ans(i, j) = sum;
            }
        }
    }
    return ans;
}

#endif //UTILS_HPP_MATRIX_H
