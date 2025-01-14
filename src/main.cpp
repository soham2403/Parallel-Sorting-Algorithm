#include "include/mergeSort.hpp"
#include "include/parallelMergeSort.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

const int SIZE = 10000000; // Increased size to better show the difference
const int NUM_TRIALS = 5;  // Run multiple trials for more reliable results

bool isSorted(const std::vector<int> &nums) {
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] < nums[i - 1]) {
            return false;
        }
    }
    return true;
}

std::vector<int> generateRandomArray(int size) {
    std::vector<int> nums(size);
    for (int i = 0; i < size; i++) {
        nums[i] = rand() % size;
    }
    return nums;
}

void printArray(const std::vector<int> &nums, int limit = 10) {
    for (int i = 0; i < limit && i < nums.size(); i++) {
        std::cout << nums[i] << " ";
    }
    std::cout << "...\n";
}

int main() {
    std::cout << "Comparing Regular Merge Sort vs Parallel Merge Sort\n";
    std::cout << "Array size: " << SIZE << "\n";
    std::cout << "Number of trials: " << NUM_TRIALS << "\n\n";

    double avg_regular = 0.0;
    double avg_parallel = 0.0;

    for (int trial = 0; trial < NUM_TRIALS; trial++) {
        std::cout << "\nTrial " << trial + 1 << ":\n";

        // Generate the same random array for both sorts
        auto original = generateRandomArray(SIZE);

        // Test regular merge sort
        {
            auto nums = original; // Make a copy
            std::cout << "Regular Merge Sort - Initial array: ";
            printArray(nums);

            MergeSort mergesort(&nums);
            auto start = std::chrono::high_resolution_clock::now();
            mergesort.sort();
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;

            std::cout << "Sorted array: ";
            printArray(nums);
            std::cout << "Time taken: " << std::fixed << std::setprecision(4)
                      << duration.count() << " seconds\n";
            std::cout << "Correctly sorted: " << (isSorted(nums) ? "Yes" : "No")
                      << "\n";

            avg_regular += duration.count();
        }

        // Test parallel merge sort
        {
            auto nums = original; // Make a copy
            std::cout << "\nParallel Merge Sort - Initial array: ";
            printArray(nums);

            ParallelMergeSort pms(&nums);
            auto start = std::chrono::high_resolution_clock::now();
            pms.sort();
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;

            std::cout << "Sorted array: ";
            printArray(nums);
            std::cout << "Time taken: " << std::fixed << std::setprecision(4)
                      << duration.count() << " seconds\n";
            std::cout << "Correctly sorted: " << (isSorted(nums) ? "Yes" : "No")
                      << "\n";

            avg_parallel += duration.count();
        }
    }

    // Calculate and display averages
    avg_regular /= NUM_TRIALS;
    avg_parallel /= NUM_TRIALS;

    std::cout << "\nResults Summary:\n";
    std::cout << "Average Regular Merge Sort time: " << std::fixed
              << std::setprecision(4) << avg_regular << " seconds\n";
    std::cout << "Average Parallel Merge Sort time: " << avg_parallel
              << " seconds\n";
    std::cout << "Speedup: " << (avg_regular / avg_parallel) << "x\n";

    return 0;
}