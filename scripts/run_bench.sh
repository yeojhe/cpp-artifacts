#!/usr/bin/env bash
set -euo pipefail
cmake --preset release -S .
cmake --build build/release -j
cmake --build build/release --target perf
echo "CSV at build/release/perf/bench_results.csv"
