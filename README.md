
# cpp-lab (AM-P00)

Frictionless C++ lab with CI, sanitizers, tidy/format, tests, and benchmarks.

## Quick start

```bash
# Configure + build (ASAN)
cmake --preset asan -S .
cmake --build build/asan -j

# Run tests
ctest --test-dir build/asan --output-on-failure

# Run the app
./build/asan/cpp_lab

# Run benchmarks and save CSV
cmake --build build/asan --target perf
ls build/asan/perf/bench_results.csv
```

## Presets

- `debug`, `release`, `asan`, `ubsan`, `tsan`

## What’s included

- **CMake 3.20+** with Ninja, warnings-as-errors, LTO (non-Debug)
- **Sanitizers**: Address/UB/Thread (opt-in via presets)
- **clang-tidy** + **clang-format** (Google-ish)
- **GTest** unit tests & **Google Benchmark**
- Example **consistent hashing** lib to iterate on in later tokens
- GitHub Actions CI: build, format check, tests, tidy, benchmarks

## Make it yours

- Add more libs under `src/`
- Add tests to `tests/`
- Add benches to `bench/`
- Store flamegraphs/CSVs under `perf/`
