cmake_minimum_required(VERSION 3.10)
project(SortBenchmark LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/O2 /LTGC)
else()
    add_compile_options(-O3 -march=native -flto)
endif()

find_package(benchmark QUIET)

if(NOT benchmark_FOUND)
    message(STATUS "Google Benchmark não encontrado no sistema. Baixando v1.9.1 via FetchContent...")
    include(FetchContent)
    FetchContent_Declare(
      google_benchmark
      GIT_REPOSITORY https://github.com/google/benchmark.git
      GIT_TAG        v1.9.1
    )
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
    set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(google_benchmark)
endif()

# Garante que o binário final vá para build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Aponta para os arquivos dentro de src/
add_executable(sortbenchmark src/benchmark.cpp)

# Linkagem com a biblioteca baixada
target_link_libraries(sortbenchmark PRIVATE benchmark::benchmark)