#pragma once
#include <cstdlib>
#include <utility>
#include <vector>

inline int partition(int *array, int start, int end) {

    int random_index = start + rand() % (end - start + 1);

    std::swap(array[random_index], array[end]);

    int pivot = array[end];
    int i = start - 1;

    for (int j = start; j < end; j++) {
        if (array[j] <= pivot) {
            i++;
            std::swap(array[i], array[j]);
        }
    }

    std::swap(array[i + 1], array[end]);

    return i + 1;
}

void quick_sort(int *array, int start, int end) {
    if (start < end) {

        int pivot_index = partition(array, start, end);

        quick_sort(array, start, pivot_index - 1);
        quick_sort(array, pivot_index + 1, end);
    }
}

void quick_sort(std::vector<int> &array) {
    if (array.empty())
        return;

    quick_sort(array.data(), 0, array.size() - 1);
}