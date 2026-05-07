#include <benchmark/benchmark.h>

#include <random>
#include <vector>

#include "mergesort.hpp"
#include "utils.hpp"

// Defines SortAlgorithm as a function that receives a vector of integers
using SortAlgorithm = void (*)(std::vector<int> &);

// Generic function for benchmarking sorting algorithms
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

BENCHMARK_TEMPLATE(BM_Sort, merge_sort)
    ->Arg(1000000)
    ->Arg(2000000)
    ->Arg(3000000)
    ->Arg(4000000)
    ->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();