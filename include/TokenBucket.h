#pragma once

#include <string>
#include <unordered_map>
#include <mutex>
#include "1_RateLimitStrategy.h"

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
    std::mutex mutex;

public:
    TokenBucket(int capacity, double refillRate);

    bool allowRequest(const std::string& userId) override;
};