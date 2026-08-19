#include "FixedWindow.h"
#include <chrono>

FixedWindow::FixedWindow(int maxRequests, int windowSize)
    : maxRequests(maxRequests), windowSize(windowSize) {}

size_t FixedWindow::shardIndex(const std::string& key) const {
    return std::hash<std::string>{}(key) % NUM_SHARDS;
}

void FixedWindow::evictStale(int shardIdx, long long now) {
    auto& map = shards[shardIdx];

    for (auto it = map.begin(); it != map.end();) {
        if (now - it->second.lastAccess > STALE_AFTER_SECONDS)
            it = map.erase(it);
        else
            ++it;
    }
}

bool FixedWindow::allowRequest(const std::string& userId) {
    long long now = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();

    size_t idx = shardIndex(userId);
    std::lock_guard<std::mutex> lock(shardMutexes[idx]);

    if (shards[idx].size() % 50 == 0 && !shards[idx].empty())
        evictStale(idx, now);

    auto& window = shards[idx][userId];
    window.lastAccess = now;

    if (window.startTime == 0 ||
        now - window.startTime >= windowSize) {
        window.startTime = now;
        window.requestCount = 0;
    }

    if (window.requestCount >= maxRequests)
        return false;

    window.requestCount++;

    return true;
}