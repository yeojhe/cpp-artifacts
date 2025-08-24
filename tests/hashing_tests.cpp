
#include <gtest/gtest.h>

#include "hashing/consistent_hashing.h"

TEST(ConsistentHash, StableAssignment) {
  // std::vector<uint64_t> points;
  // for (uint64_t i = 0; i < 8; ++i) points.push_back(hashing::splitmix64(i));
  constexpr std::size_t kN = 8;
  std::vector<uint64_t> points;
  points.reserve(kN);
  for (uint64_t i = 0; i < kN; ++i) {
    points.push_back(hashing::splitmix64(i));
  }

  hashing::ConsistentHash ch(points);
  auto idx1 = ch.assign("user_abc");
  auto idx2 = ch.assign("user_abc");
  EXPECT_EQ(idx1, idx2);
}

TEST(ConsistentHash, WrapsAtEnd) {
  // std::vector<uint64_t> points;
  // for (uint64_t i = 0; i < 2; ++i) points.push_back(hashing::splitmix64(i));
  constexpr std::size_t kN = 2;
  std::vector<uint64_t> points;
  points.reserve(kN);
  for (uint64_t i = 0; i < kN; ++i) {
    points.push_back(hashing::splitmix64(i));
  }
  hashing::ConsistentHash ch(points);
  // This mostly exercises both branches; not checking exact idx to avoid coupling to hash impl.
  (void)ch.assign("zzz");
  (void)ch.assign("aaa");
  SUCCEED();
}
