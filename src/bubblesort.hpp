#pragma once
#include <vector>

void bubble_sort(int *array, size_t size) {
    while (size > 0) {
        bool swapped = false;
        for (size_t i = 0; i < size - 1; i++) {
            int a = array[i];
            int b = array[i + 1];
            bool cond = a > b;

            array[i] = cond ? b : a;
            array[i + 1] = cond ? a : b;

            swapped |= cond;
        }
        size--;

        if (!swapped)
            return;
    }
}

void bubble_sort(std::vector<int> &v) {
    if (v.empty())
        return;
    bubble_sort(v.data(), v.size());
}