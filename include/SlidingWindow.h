#pragma once

#include "1_RateLimitStrategy.h"
#include <deque>
#include <unordered_map>
#include <chrono>

class SlidingWindow : public IRateLimitStrategy
{
private:
    int maxRequests;
    int windowSize;
    std::unordered_map<std::string, std::deque<long long>> requests;

public:
    SlidingWindow(int maxRequests, int windowSize);

    bool allowRequest(const std::string& userId) override;
};