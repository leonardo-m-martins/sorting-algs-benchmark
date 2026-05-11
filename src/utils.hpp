#pragma once
#include <algorithm>
#include <random>
#include <vector>

namespace benchmark_utils {
// Define sort_algorithm como uma função void que recebe um vetor de inteiros
// Isso é usado para criar funções genéricas para cada tipo de algoritmo
using sort_algorithm = void (*)(std::vector<int> &);

// Tipo genérico para uma função qualquer que gera um vetor de inteiros.
using vector_generator = std::vector<int> (*)(size_t n);

// Gera um vetor com dados aleatórios
std::vector<int> generate_random_vector(size_t n) {
    std::vector<int> v(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    for (int &i : v)
        i = dis(gen);
    return v;
}

// Gera um vetor ordenado em ordem crescente
std::vector<int> generate_ascending_vector(size_t n) {
    std::vector<int> v(n);
    int i = 0;
    for (int &element : v)
        element = i++;
    return v;
}

// Gera um vetor ordenado em ordem decrescente
std::vector<int> generate_descending_vector(size_t n) {
    std::vector<int> v(n);
    int i = n;
    for (int &element : v)
        element = i--;
    return v;
}

// Verifica se um vetor está ordenado
bool is_sorted(std::vector<int> &v) {
    int last = v.at(0);
    for (int n : v) {
        if (n < last)
            return false;
        last = n;
    }
    return true;
}

} // namespace benchmark_utils