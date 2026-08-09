#pragma once

#include <string>
#include <unordered_map>
#include <mutex>
#include "1_RateLimitStrategy.h"

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

    std::unordered_map<std::string, Window> windows;
    std::mutex mutex;

public:
    FixedWindow(int maxRequests, int windowSize);

    bool allowRequest(const std::string& userId) override;
};