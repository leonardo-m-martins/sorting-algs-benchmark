#include <benchmark/benchmark.h>

#include <random>
#include <vector>

#include "bubblesort.hpp"
#include "mergesort.hpp"
#include "radixsort.hpp"
#include "selectionsort.hpp"
#include "utils.hpp"
#include "bubblesort.hpp"
#include "heapsort.hpp"
#include "insertionsort.hpp"
#include "quicksort.hpp"

/**
 * Macro usado para fazer o benchmark de um agoritmo pelos 3 tipos de dados requisitados:
 * aleatório, ordenado (crescente), ordenado (decrescente).
 * Params:
 *  alg: algoritmo de ordenação do tipo sort_algorithm
 *  settings: aplica as configurações do benchmark
 */
#define BENCHMARK_SORT(alg, settings)                                                                                            \
    BENCHMARK_TEMPLATE(BM_sort, alg, generate_random_vector)->Apply(settings);                                  \
    BENCHMARK_TEMPLATE(BM_sort, alg, generate_ascending_vector)->Apply(settings);                               \
    BENCHMARK_TEMPLATE(BM_sort, alg, generate_descending_vector)->Apply(settings);

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

// Função de configuração de algoritmos O(NlogN) ou O(N)
void fast_settings(benchmark::internal::Benchmark *benchmark) {
    benchmark
        ->Arg(1000000)
        ->Arg(2000000)
        ->Arg(4000000)
        ->Iterations(3)
        ->Unit(benchmark::kMicrosecond);
}

// Função de configuração de algoritmos O(N²)
void slow_settings(benchmark::internal::Benchmark *benchmark) {
    benchmark
        ->Arg(62500)
        ->Unit(benchmark::kSecond);
}

// Inserir chamadas para benchmark abaixo
BENCHMARK_SORT(merge_sort, fast_settings);
BENCHMARK_SORT(radix_sort, fast_settings);
BENCHMARK_SORT(selection_sort, fast_settings);
BENCHMARK_SORT(bubble_sort, fast_settings);
BENCHMARK_SORT(heap_sort, fast_settings);
BENCHMARK_SORT(quick_sort, fast_settings);
BENCHMARK_SORT(insertion_sort, fast_settings);

BENCHMARK_MAIN();