
#include <iostream>
#include "hashing/consistent_hashing.h"

int main() {
    std::vector<uint64_t> points;
    for (uint64_t i = 0; i < 1024; ++i) points.push_back(hashing::splitmix64(i));
    hashing::ConsistentHash ch(points);
    std::cout << "Bucket index for user_123: " << ch.assign("user_123") << "\n";
    return 0;
}
