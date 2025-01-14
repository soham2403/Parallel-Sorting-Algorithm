#ifndef PARALLEL_MERGE_SORT_H
#define PARALLEL_MERGE_SORT_H
#include <bits/stdc++.h>

class ParallelMergeSort {
  private:
    std::vector<int> *nums;

  public:
    ParallelMergeSort(std::vector<int> *nums);
    ~ParallelMergeSort();
    void sort();
    void ParallelRecursiveSort(int left, int right);
};

#endif