#pragma once
#include <vector>

inline void heapify(std::vector<int> &arr, int n, int i) {
    while (true) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) { // check left
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) { // check right
            largest = right;
        }

        if (largest == i) { // already fixed
            break;
        }
        
        std::swap(arr[i], arr[largest]);
        i = largest;
    }
}

inline void build_max_heap(std::vector<int> &arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

inline void heap_sort(std::vector<int> &arr) {
    int n = arr.size();
    
    build_max_heap(arr, n);
    
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}