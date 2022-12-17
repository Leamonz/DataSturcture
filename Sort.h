//
// Created by HP on 2022/12/12.
//

#ifndef MAIN_CPP_SORT_H
#define MAIN_CPP_SORT_H

template<class ElemType>
void StraightInsertSort(ElemType *arr, int n) {
    for (int i = 1; i < n; i++) {
        ElemType elem = arr[i];
        int j;
        for (j = i - 1; j >= 0 && arr[j] > elem; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = elem;
    }
}

template<class ElemType>
void ShellInsert(ElemType *arr, int n, int incr) {
    // 将原序列分解为多个子序列，然后对子序列进行排序
    for (int i = incr; i < n; i += incr) {
        ElemType elem = arr[i];
        int j;
        for (j = i - incr; j >= 0 && arr[j] > elem; j -= incr) {
            arr[j + incr] = arr[j];
        }
        arr[j + incr] = elem;
    }
}

template<class ElemType>
void ShellSort(ElemType *arr, int n, int *inc, int t) {
    for (int k = 0; k < t; k++) {
        ShellInsert(arr, n, inc[k]);
    }
}

template<class ElemType>
void BubbleSort(ElemType *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

template<class ElemType>
void QuickSort(ElemType *arr, int l, int r) {
    if (l >= r) {
        return;
    }
    int L = l, R = r;
    int pivot = (l + r) / 2;
    while (l < pivot && r > pivot) {
        if (arr[l] > arr[pivot]) {
            int temp = arr[pivot];
            arr[pivot] = arr[l];
            arr[l] = temp;
        } else {
            l++;
        }
        if (arr[r] < arr[pivot]) {
            int temp = arr[pivot];
            arr[pivot] = arr[r];
            arr[r] = temp;
        } else {
            r--;
        }
    }
    QuickSort(arr, L, pivot);
    QuickSort(arr, pivot + 1, R);
}

template<class ElemType>
void SelectSort(ElemType *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minPos = i;
        for (int j = minPos + 1; j < n; j++) {
            if (arr[j] < arr[minPos]) {
                minPos = j;
            }
        }
        if (minPos != i) {
            int temp = arr[minPos];
            arr[minPos] = arr[i];
            arr[i] = temp;
        }
    }
}

template<class ElemType>
void MergeSort(ElemType *arr, int l, int r) {
    if (l >= r) {
        return;
    }
    int mid = (l + r) / 2;
    MergeSort(arr, l, mid);
    MergeSort(arr, mid + 1, r);
    auto *brr = new ElemType[r - l + 1];
    int len = 0;
    int L = l, R = mid + 1;
    while (L <= mid && R <= r) {
        if (arr[L] < arr[R]) {
            brr[len++] = arr[L++];
        } else {
            brr[len++] = arr[R++];
        }
    }
    while (L <= mid) {
        brr[len++] = arr[L++];
    }
    while (R <= r) {
        brr[len++] = arr[R++];
    }
    for (int i = 0, j = l; j <= r; j++, i++) {
        arr[j] = brr[i];
    }
    delete[] brr;
}

template<class ElemType>
void CountingSort(ElemType *arr, int n) {
    int *count = new int[n]{};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j != i) {
                count[i] += arr[i] > arr[j] ? 1 : 0;
            }
        }
    }
    int *brr = new ElemType[n];
    for (int i = 0; i < n; i++) {
        brr[count[i]] = arr[i];
    }
    for (int i = 0; i < n; i++) {
        arr[i] = brr[i];
    }
    delete[] brr;
    delete[] count;
}

#endif //MAIN_CPP_SORT_H
