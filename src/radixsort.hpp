#include <vector>
#include <cstring>

typedef struct {
    int max;
    int min;
} vector_info;

vector_info get_vector_info(int *array, size_t size) {
    vector_info v_info = {array[0], array[0]};
    for (int i = 0; i < size; i++) {
        if (array[i] > v_info.max) v_info.max = array[i];
        else if (array[i] < v_info.min) v_info.min = array[i];
    }

    return v_info;
}

bool radix_sort(int *array, int *aux, size_t size) {
    const int shift = 8;
    const int base = 1 << shift;
    const int mask = base - 1;

    vector_info v_info = get_vector_info(array, size);

    const unsigned int offset = (v_info.min < 0) ? -static_cast<unsigned int>(v_info.min) : 0;
    const unsigned int max_val = v_info.max + offset;

    int passes = 0;

    for (int exp = 0; exp < (shift * sizeof(int)) && (max_val >> exp) > 0; exp += shift) {
        size_t bucket[base] = {0};

        // conta quantos elementos de cada digito existem
        for (int i = 0; i < size; i++) {
            unsigned int number = array[i] + offset;
            int digit = number >> exp & mask;
            bucket[digit]++;
        }

        // adiciona offsets para ordenar cada digito no array
        for (int i = 1; i < base; i++) {
            bucket[i] += bucket[i - 1];
        }

        // adiciona os elementos em aux, ordenados pelo digito
        for (int i = size - 1; i >= 0; i--) {
            unsigned int number = array[i] + offset;
            int digit = number >> exp & mask;
            size_t idx = --bucket[digit];
            aux[idx] = array[i];
        }

        std::swap(array, aux);
        passes++;
    }

    return passes % 2 != 0;
}

void radix_sort(std::vector<int> &v) {
    std::vector<int> aux(v.size());
    bool swapped = radix_sort(v.data(), aux.data(), v.size());
    if (swapped)
        std::swap(v, aux);
}