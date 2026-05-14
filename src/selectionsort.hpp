#pragma once
#include <vector>
#include <utility>
#include <cstdint>

inline void selection_sort(std::vector<int> &array) {
	uint32_t size = array.size();
	for (uint32_t i = 0; i < size - 1; i++) {
		uint32_t min_idx = i;
		for (uint32_t j = i + 1; j < size; j++) {
			if (array[min_idx] > array[j]) {
				min_idx = j;
			}
		}
		if (min_idx != i) {
			std::swap(array[i], array[min_idx]);
		}
	}
}