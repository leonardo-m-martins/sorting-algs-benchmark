cmake_minimum_required(VERSION 3.10)
project(SortBenchmark LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/O2 /LTGC)
else()
    add_compile_options(-O3 -march=native -flto)
endif()

find_package(benchmark REQUIRED)

# Garante que o binário final vá para build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Aponta para os arquivos dentro de src/
add_executable(sortbenchmark src/benchmark.cpp)

target_link_libraries(sortbenchmark benchmark::benchmark)