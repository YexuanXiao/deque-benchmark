cmake_minimum_required(VERSION 3.29)

project(deque-benchmark)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BENCHMARK_ENABLE_DOXYGEN OFF)
set(BENCHMARK_ENABLE_INSTALL OFF)
set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(benchmark EXCLUDE_FROM_ALL)

add_executable(bench-bizwen benchmark.cpp)
target_link_libraries(bench-bizwen PRIVATE benchmark::benchmark)

add_executable(bench-std benchmark.cpp)
target_link_libraries(bench-std PRIVATE benchmark::benchmark)
target_compile_definitions(bench-std PRIVATE TEST_STD)
