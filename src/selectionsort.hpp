#pragma once
#include <cstdint>
#include <utility>
#include <vector>

// Versão escalar do selection sort
void _selection_sort(int *array, uint32_t size) {
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

#ifdef __AVX2__

#include <immintrin.h>

/**
 * Função helper para obter o menor valor e seu indice de maneira escalar.
 * Usado na versão SIMD.
 */
inline void find_min(int *array, int *min_ptr, uint32_t *min_idx_ptr, uint32_t start, uint32_t size) {
    for (int i = start; i < size; i++) {
        if (array[i] < *min_ptr) {
            *min_ptr = array[i];
            *min_idx_ptr = i;
        }
    }
}

// Versão feita com SIMD
__attribute__((target("avx2"))) void selection_sort(int *array, uint32_t size) {
    if (size < 8)
        _selection_sort(array, size);

    const __m256i eights = _mm256_set1_epi32(8);

    for (uint32_t i = 0; i < size - 1; i++) {
        // setar min_vals e min_idxs todos com array[i] e i
        __m256i min_vals = _mm256_set1_epi32(array[i]);
        __m256i min_idxs = _mm256_set1_epi32(i);

        // prepara idxs para o loop interno
        uint32_t j = i + 1;
        __m256i curr_idxs = _mm256_setr_epi32(j, j + 1, j + 2, j + 3, j + 4, j + 5, j + 6, j + 7);

        /**
         * O loop interno processa blocos de 8 inteiros (256 bits) por vez
         * vals = ...       lê os valores no array
         * mask = ...       compara os 8 valores em vals com os 8 valores em min_vals
         *                  e retorna uma mask[8] onde:
         *                      m em mask = 0xFFFFFFFF se val < min_val
         *                      m em mask = 0x00000000 se val >= min_val
         * min_vals = ...    para cada inteiro de 32 bits nos dois vetores, retorna o menor
         * min_idx = ...   de acordo com mask retorna os seguintes valores:
         *                      min_idx se mask = 0x00000000
         *                      curr_idx se mask = 0xFFFFFFFF
         * curr_idxs = ...  incrementa os indices em 8 cada
         * */
        constexpr uint64_t step = 8;
        constexpr uint64_t steps = 4;
        constexpr uint64_t total = step * steps;
        constexpr uint64_t total_mask = total - 1;
        int64_t range = (int64_t)size - j;
        int64_t limit = (range > total) ? (int64_t)size - (range & total_mask) : 0;
        for (; j < limit; j += total) {

#pragma unroll(steps)
            for (uint32_t k = 0; k < total; k += step) {
                __m256i vals = _mm256_loadu_si256((__m256i *)&array[j + k]);
                __m256i mask = _mm256_cmpgt_epi32(min_vals, vals);
                min_vals = _mm256_min_epi32(min_vals, vals);
                min_idxs = _mm256_blendv_epi8(min_idxs, curr_idxs, mask);
                curr_idxs = _mm256_add_epi32(curr_idxs, eights);
            }
        }

        alignas(32) int min_vals_array[8];
        alignas(32) uint32_t min_idxs_array[8];
        _mm256_store_si256((__m256i *)min_vals_array, min_vals);
        _mm256_store_si256((__m256i *)min_idxs_array, min_idxs);

        // encontrar o valor mínimo entre os 8 elementos retornados
        int min = min_vals_array[0];
        uint32_t v_idx = 0; // usado para descobrir o menor indice no array min_idxs_array
        find_min(min_vals_array, &min, &v_idx, 0, 8);

        uint32_t min_idx = min_idxs_array[v_idx];

        // Tail: O array pode não ser múltiplo de 8, então iteramos sob o restante do array
        find_min(array, &min, &min_idx, j, size);

        array[min_idx] = array[i];
        array[i] = min;
    }
}
#endif

void selection_sort(std::vector<int> &v) {
    if (v.size() < 2)
        return;

#ifdef __AVX2__
    if (__builtin_cpu_supports("avx2")) {
        selection_sort(v.data(), v.size());
        return;
    }
#endif

    _selection_sort(v.data(), v.size());
}