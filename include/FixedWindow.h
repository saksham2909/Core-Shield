#pragma once

#include "1_RateLimitStrategy.h"
#include <unordered_map>
#include <chrono>

class FixedWindow : public IRateLimitStrategy
{
private:
    int maxRequests;
    int windowSize;

    struct Window
    {
        long long startTime;
        int requestCount;
    };

    std::unordered_map<std::string, Window> users;

public:
    FixedWindow(int maxRequests, int windowSize);

    bool allowRequest(const std::string& userId) override;
};