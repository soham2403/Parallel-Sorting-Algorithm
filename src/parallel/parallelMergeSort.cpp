#include "../include/parallelMergeSort.hpp"
#include <iostream>
#include <thread>

ParallelMergeSort::ParallelMergeSort(std::vector<int> *nums) : nums(nums) {}
ParallelMergeSort::~ParallelMergeSort() {}

void ParallelMergeSort::ParallelRecursiveSort(int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    // lambda function.

    if (right - left > 10000) {

        std::thread thread1(
            [this, left, mid] { this->ParallelRecursiveSort(left, mid); });
        std::thread thread2([this, mid, right] {
            this->ParallelRecursiveSort(mid + 1, right);
        });

        thread1.join();
        thread2.join();
    } else {
        this->ParallelRecursiveSort(left, mid);
        this->ParallelRecursiveSort(mid + 1, right);
    }
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
}

void ParallelMergeSort::sort() {
    if ((*nums).empty()) {
        return;
    }
    std::thread thread1(
        [this] { this->ParallelRecursiveSort(0, ((*nums).size() - 1)); });
    thread1.join();
}