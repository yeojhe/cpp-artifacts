#include <cstdint>
#include <iostream>
#include <string_view>
#include <vector>

#include "hashing/consistent_hashing.h"

auto main() -> int {
  // named compile time constant (no magic number)
  constexpr std::size_t kPoints = 1024;
  // create an empty vector of 64-bit integers
  std::vector<uint64_t> points;
  // preallocate capacity for exactly kPoints elements
  points.reserve(kPoints);
  // loop i from 0..kPoints-1 (prefix ++ is fine)
  for (uint64_t i = 0; i < kPoints; ++i) {
    // fill vector with 64-bit hashes of i
    points.push_back(hashing::splitmix64(i));
  }

  const hashing::ConsistentHash ch(points);
  constexpr std::string_view kUser = "user_123";
  std::cout << "Bucket index for " << kUser << ": " << ch.assign(kUser) << '\n';
  return 0;
}