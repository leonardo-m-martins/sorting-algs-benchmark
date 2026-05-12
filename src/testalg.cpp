#include "mergesort.hpp"
#include "radixsort.hpp"
#include "utils.hpp"
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace benchmark_utils;

void print_is_sorted(std::vector<int> &v, std::string msg) {
    std::string sort_status = is_sorted(v) ? "Ordenado" : "Nao ordenado";
    std::cout << std::left << std::setw(20) << msg + ":" << sort_status << std::endl;
}

void test_alg(sort_algorithm sort_function, std::string func_name, std::vector<int> &v) {
    std::vector<int> vector_copy = v;
    sort_function(vector_copy);
    print_is_sorted(vector_copy, func_name);
}

int main() {
    int N = 10000;
    auto rd_vector = generate_random_vector(N);
    print_is_sorted(rd_vector, "Vetor randomico");

    test_alg(merge_sort, "Merge sort", rd_vector);
    test_alg(radix_sort, "Radix sort", rd_vector);
}