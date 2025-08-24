
#include <benchmark/benchmark.h>

#include <string>

#include "hashing/consistent_hashing.h"

static void BM_Assign(benchmark::State& state) {
  // std::vector<uint64_t> points;
  // for (uint64_t i = 0; i < 2048; ++i) points.push_back(hashing::splitmix64(i));
  constexpr std::size_t kPoints = 2048;
  std::vector<uint64_t> points;
  points.reserve(kPoints);
  for (uint64_t i = 0; i < kPoints; ++i) {
    points.push_back(hashing::splitmix64(i));
  }

  hashing::ConsistentHash ch(points);
  std::string key = "user_";
  for (auto _ : state) {
    // key.back() = static_cast<char>('0' + (state.iterations() % 10));
    constexpr int kDigits = 10;
    key.back() = static_cast<char>('0' + (state.iterations() % kDigits));
    benchmark::DoNotOptimize(ch.assign(key));
  }
}
BENCHMARK(BM_Assign)->Unit(benchmark::kNanosecond);

BENCHMARK_MAIN();  // NOLINT(modernize-avoid-c-arrays,modernize-use-trailing-return-type)
