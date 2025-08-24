
cmake_minimum_required(VERSION 3.20)
project(cpp_lab LANGUAGES CXX)

# Options
option(ENABLE_ASAN "Enable AddressSanitizer" OFF)
option(ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer" OFF)
option(ENABLE_TSAN "Enable ThreadSanitizer" OFF)
option(ENABLE_WARNINGS_AS_ERRORS "Treat warnings as errors" ON)
option(ENABLE_LTO "Enable Link Time Optimization" ON)
option(ENABLE_CLANG_TIDY "Run clang-tidy during build (if available)" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/warnings.cmake)
include(cmake/sanitizers.cmake)
include(cmake/clang_tidy.cmake)

# Dependencies via FetchContent (GTest, Google Benchmark)
include(FetchContent)

# GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Google Benchmark
FetchContent_Declare(
  benchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.8.4.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(benchmark)

# Library target (example: hashing)
add_library(hashing STATIC
    src/hashing/consistent_hashing.cpp
    src/hashing/consistent_hashing.h
)
target_include_directories(hashing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_features(hashing PUBLIC cxx_std_20)
apply_project_warnings(hashing)
apply_sanitizers(hashing)

# Executable (main)
add_executable(cpp_lab src/main.cpp)
target_link_libraries(cpp_lab PRIVATE hashing)
apply_project_warnings(cpp_lab)
apply_sanitizers(cpp_lab)

# Tests
enable_testing()
add_executable(hashing_tests tests/hashing_tests.cpp)
target_link_libraries(hashing_tests PRIVATE hashing GTest::gtest_main)
apply_project_warnings(hashing_tests)
apply_sanitizers(hashing_tests)
include(GoogleTest)
gtest_discover_tests(hashing_tests)

# Benchmarks
add_executable(hashing_bench bench/hashing_bench.cpp)
target_link_libraries(hashing_bench PRIVATE hashing benchmark::benchmark)
apply_project_warnings(hashing_bench)
apply_sanitizers(hashing_bench)

# Perf helper target
add_custom_target(perf
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/perf
    COMMAND hashing_bench --benchmark_format=csv --benchmark_out=${CMAKE_SOURCE_DIR}/perf/bench_results.csv
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running benchmarks and saving CSV to ${CMAKE_SOURCE_DIR}/perf/bench_results.csv"
)

enable_tidy(hashing)
enable_tidy(cpp_lab)
enable_tidy(hashing_tests)
enable_tidy(hashing_bench)