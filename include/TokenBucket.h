#pragma once

#include "1_RateLimitStrategy.h"
#include <unordered_map>
#include <chrono>
#include <algorithm>

class TokenBucket : public IRateLimitStrategy
{
private:
    int capacity;
    double refillRate;

    struct Bucket
    {
        double tokens;
        long long lastRefill;
    };

    std::unordered_map<std::string, Bucket> users;

public:
    TokenBucket(int capacity, double refillRate);

    bool allowRequest(const std::string& userId) override;
};