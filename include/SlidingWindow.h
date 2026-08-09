#pragma once

#include <string>
#include <unordered_map>
#include <deque>
#include <mutex>
#include "1_RateLimitStrategy.h"

class SlidingWindow : public IRateLimitStrategy
{
private:
    int maxRequests;
    int windowSize;

    std::unordered_map<std::string, std::deque<long long>> requests;
    std::mutex mutex;

public:
    SlidingWindow(int maxRequests, int windowSize);

    bool allowRequest(const std::string& userId) override;
};