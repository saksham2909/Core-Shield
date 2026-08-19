#include "TokenBucket.h"
#include <chrono>
#include <algorithm>

TokenBucket::TokenBucket(int maxRequests, int windowSize)
    : maxRequests(maxRequests), windowSize(windowSize) {}

size_t TokenBucket::shardIndex(const std::string& key) const {
    return std::hash<std::string>{}(key) % NUM_SHARDS;
}

void TokenBucket::evictStale(int shardIdx, long long now) {
    auto& map = shards[shardIdx];

    for (auto it = map.begin(); it != map.end();) {
        if (now - it->second.lastAccess > STALE_AFTER_SECONDS)
            it = map.erase(it);
        else
            ++it;
    }
}

bool TokenBucket::allowRequest(const std::string& userId) {
    long long now = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();

    size_t idx = shardIndex(userId);
    std::lock_guard<std::mutex> lock(shardMutexes[idx]);

    if (shards[idx].size() % 50 == 0 && !shards[idx].empty())
        evictStale(idx, now);

    auto& bucket = shards[idx][userId];

    if (bucket.lastRefill == 0) {
        bucket.tokens = maxRequests;
        bucket.lastRefill = now;
    }

    double refillRate = static_cast<double>(maxRequests) / windowSize;
    double elapsed = now - bucket.lastRefill;

    bucket.tokens = std::min(
        static_cast<double>(maxRequests),
        bucket.tokens + elapsed * refillRate
    );

    bucket.lastRefill = now;
    bucket.lastAccess = now;

    if (bucket.tokens < 1)
        return false;

    bucket.tokens--;

    return true;
}