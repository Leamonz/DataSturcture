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
        if (elems != nullptr) {
            delete[] elems;
            elems = nullptr;
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
    delete[] elems;
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

template<class ElemType>
class Triple {
protected:
    int rows, cols;
    ElemType elem{};
public:
    Triple();

    Triple(int r, int c, ElemType e);

    Triple(const Triple<ElemType> &copy);
};

template<class ElemType>
Triple<ElemType>::Triple() {
    rows = 0;
    cols = 0;
}

template<class ElemType>
Triple<ElemType>::Triple(int r, int c, ElemType e) {
    rows = r;
    cols = c;
    elem = e;
}

template<class ElemType>
Triple<ElemType>::Triple(const Triple<ElemType> &copy) {
    if (&copy != this) {
        rows = copy.rows;
        cols = copy.cols;
        elem = copy.elem;
    }
}

template<class ElemType>
class SparseMatrix {
protected:
    pair<int, int> shape;
    SimpleLinkList<Triple<ElemType>> *elems;
public:
    explicit SparseMatrix(const SimpleLinkList<Triple<ElemType>> &copy, int r = 100, int c = 100);

    int GetRows() const;

    int GetCols() const;

    int GetNum() const;

    bool Empty() const;

    bool SetElem(int x, int y, ElemType &elem);

    bool GetElem(int x, int y, ElemType &elem) const;

    ElemType &operator()(int x, int y) const;

    ~SparseMatrix();
};

template<class ElemType>
SparseMatrix<ElemType>::SparseMatrix(const SimpleLinkList<Triple<ElemType>> &copy, int r, int c) {
    shape = make_pair(r, c);
    elems = new SimpleLinkList<Triple<ElemType>>(r * c);
    Triple<ElemType> temp;
    for (int i = 1; i <= copy.Length(); i++) {
        copy.GetElem(i, temp);
        elems->Insert(i, temp);
    }
}

template<class ElemType>
int SparseMatrix<ElemType>::GetRows() const {
    return shape.first;
}

template<class ElemType>
int SparseMatrix<ElemType>::GetCols() const {
    return shape.second;
}

template<class ElemType>
int SparseMatrix<ElemType>::GetNum() const {
    return elems->Length();
}

template<class ElemType>
bool SparseMatrix<ElemType>::Empty() const {
    return elems->Empty();
}

template<class ElemType>
bool SparseMatrix<ElemType>::SetElem(int x, int y, ElemType &elem) {
    Triple<ElemType> temp;
    for (int i = 1; i <= elems->Length(); i++) {
        elems->GetElem(i, temp);
        if (temp.rows == x && temp.cols == y) {
            elems->SetElem(i, Triple<ElemType>(x, y, elem));
            return true;
        }
    }
    return false;
}

template<class ElemType>
bool SparseMatrix<ElemType>::GetElem(int x, int y, ElemType &elem) const {
    Triple<ElemType> temp;
    for (int i = 1; i <= elems->Length(); i++) {
        elems->GetElem(i, temp);
        if (temp.rows == x && temp.cols == y) {
            elem = temp.elem;
            return true;
        }
    }
    return false;
}

template<class ElemType>
ElemType &SparseMatrix<ElemType>::operator()(int x, int y) const {
    Triple<ElemType> temp;
    for (int i = 1; i <= elems->Length(); i++) {
        elems->GetElem(temp);
        if (temp.rows == x && temp.cols == y) {
            return temp.elem;
        }
    }
    cout << "Can't find elem on position: (" << x << "," << y << ")" << endl;
    exit(1);
}

template<class ElemType>
SparseMatrix<ElemType>::~SparseMatrix() {
    delete elems;
}


#endif //UTILS_HPP_MATRIX_H
