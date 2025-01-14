#include "../include/mergeSort.hpp"
#include <iostream>

MergeSort::MergeSort(std::vector<int> *nums) { this->nums = nums; }
MergeSort::~MergeSort() {}

void MergeSort::recursiveSort(int left, int right) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;

    recursiveSort(left, mid);
    recursiveSort(mid + 1, right);

    std::vector<int> temp;
    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right) {
        if ((*nums)[i] <= (*nums)[j]) {
            temp.push_back((*nums)[i]);
            i++;
        } else {
            temp.push_back((*nums)[j]);
            j++;
        }
    }

    while (i <= mid) {
        temp.push_back((*nums)[i]);
        i++;
    }
    while (j <= right) {
        temp.push_back((*nums)[j]);
        j++;
    }
    for (int k = left; k <= right; k++) {
        (*nums)[k] = temp[k - left];
    }
    return;
}
void MergeSort::sort() {
    if ((*nums).empty()) {
        return;
    }
    recursiveSort(0, (*nums).size() - 1);
}