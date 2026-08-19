#include "SlidingWindow.h"
#include <chrono>

SlidingWindow::SlidingWindow(int maxRequests, int windowSize)
    : maxRequests(maxRequests), windowSize(windowSize) {}

size_t SlidingWindow::shardIndex(const std::string& key) const {
    return std::hash<std::string>{}(key) % NUM_SHARDS;
}

void SlidingWindow::evictStale(int shardIdx, long long now) {
    auto& map = shards[shardIdx];

    for (auto it = map.begin(); it != map.end();) {
        if (now - it->second.lastAccess > STALE_AFTER_SECONDS)
            it = map.erase(it);
        else
            ++it;
    }
}

bool SlidingWindow::allowRequest(const std::string& userId) {
    long long now = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();

    size_t idx = shardIndex(userId);
    std::lock_guard<std::mutex> lock(shardMutexes[idx]);

    if (shards[idx].size() % 50 == 0 && !shards[idx].empty())
        evictStale(idx, now);

    auto& user = shards[idx][userId];
    user.lastAccess = now;

    while (!user.timestamps.empty() &&
           now - user.timestamps.front() >= windowSize) {
        user.timestamps.pop_front();
    }

    if (static_cast<int>(user.timestamps.size()) >= maxRequests)
        return false;

    user.timestamps.push_back(now);

    return true;
}