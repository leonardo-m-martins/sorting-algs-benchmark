#pragma once
#include <vector>
#include <random>
#include <algorithm>

namespace benchmark_utils {
    // Gera um vetor com dados aleatórios
    inline std::vector<int> generate_random_vector(size_t n) {
        std::vector<int> v(n);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 1000000);
        for (int& i : v) i = dis(gen);
        return v;
    }
}