#include <benchmark/benchmark.h>

#include <random>
#include <vector>

#include "mergesort.hpp"
#include "radixsort.hpp"
#include "utils.hpp"

/**
 * Macro usado para fazer o benchmark de um agoritmo pelos 3 tipos de dados requisitados:
 * aleatório, ordenado (crescente), ordenado (decrescente).
 */
#define BENCHMARK_SORT(alg)                                                                                            \
    BENCHMARK_TEMPLATE(BM_sort, alg, generate_random_vector)->Apply(config_settings);                                  \
    BENCHMARK_TEMPLATE(BM_sort, alg, generate_ascending_vector)->Apply(config_settings);                               \
    BENCHMARK_TEMPLATE(BM_sort, alg, generate_descending_vector)->Apply(config_settings);

using namespace benchmark_utils;

// Função genérica para fazer o benchmark de um algoritmo de ordenação qualquer
template <sort_algorithm sort_function, vector_generator generate_vector> static void BM_sort(benchmark::State &state) {
    const int N = state.range(0);

    for (auto _ : state) {
        state.PauseTiming();
        std::vector<int> v = generate_vector(N);
        state.ResumeTiming();

        sort_function(v);

        benchmark::DoNotOptimize(v.data());
    }
    state.SetComplexityN(N);
}

// Função que de configuração de todos os benchmarks
void config_settings(benchmark::internal::Benchmark *benchmark) {
    benchmark
        ->Arg(1000000)
        ->Arg(2000000)
        ->Arg(4000000)
        ->Unit(benchmark::kMicrosecond);
}

// Inserir chamadas para benchmark abaixo
BENCHMARK_SORT(merge_sort);
BENCHMARK_SORT(radix_sort);

BENCHMARK_MAIN();