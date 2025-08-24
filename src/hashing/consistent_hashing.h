
#pragma once
#include <cstdint>
#include <vector>
#include <string_view>
#include <functional>
#include <algorithm>

namespace hashing {

// A simple, stable 64-bit hash (splitmix64).
inline uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

class ConsistentHash {
public:
    explicit ConsistentHash(std::vector<uint64_t> ring_points)
        : ring_(std::move(ring_points)) {
        std::sort(ring_.begin(), ring_.end());
    }

    // Map key -> ring point index (for now expose index; future: bucket id mapping).
    size_t assign(std::string_view key) const {
        uint64_t h = splitmix64(std::hash<std::string_view>{}(key));
        auto it = std::lower_bound(ring_.begin(), ring_.end(), h);
        if (it == ring_.end()) return 0;
        return static_cast<size_t>(std::distance(ring_.begin(), it));
    }

    const std::vector<uint64_t>& ring() const { return ring_; }

private:
    std::vector<uint64_t> ring_;
};

} // namespace hashing
