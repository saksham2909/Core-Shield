#pragma once

#include "IRateLimitStrategy.h"
#include <string>
#include <unordered_map>
#include <mutex>
#include <array>

class FixedWindow : public IRateLimitStrategy {
public:
    FixedWindow(int maxRequests, int windowSize);
    bool allowRequest(const std::string& userId) override;

private:
    struct Window {
        long long startTime = 0;
        int requestCount = 0;
        long long lastAccess = 0;
    };

    static const int NUM_SHARDS = 16;
    static const long long STALE_AFTER_SECONDS = 300;

    int maxRequests;
    int windowSize;

    std::array<std::unordered_map<std::string, Window>, NUM_SHARDS> shards;
    std::array<std::mutex, NUM_SHARDS> shardMutexes;

    size_t shardIndex(const std::string& key) const;
    void evictStale(int shardIdx, long long now);
};