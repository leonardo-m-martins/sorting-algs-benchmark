#include <benchmark/benchmark.h>

#include <random>
#include <vector>

#include "mergesort.hpp"
#include "utils.hpp"

// Define SortAlgorithm como uma função void que recebe um vetor de inteiros
using SortAlgorithm = void (*)(std::vector<int> &);

// Função genérica para fazer o benchmark de um algoritmo de ordenação qualquer
template <SortAlgorithm SortFunc> static void BM_Sort(benchmark::State &state) {
    const int N = state.range(0);

    for (auto _ : state) {
        state.PauseTiming();
        auto v = benchmark_utils::generate_random_vector(N);
        state.ResumeTiming();

        SortFunc(v);

        benchmark::DoNotOptimize(v.data());
    }
    state.SetComplexityN(N);
}

// Faz o benchmark do merge_sort para 1, 2, 3 e 4 milhões de elementos
BENCHMARK_TEMPLATE(BM_Sort, merge_sort)
    ->Arg(1000000)
    ->Arg(2000000)
    ->Arg(3000000)
    ->Arg(4000000)
    ->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();