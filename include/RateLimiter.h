#pragma once

#include <string>
#include "IRateLimitStrategy.h"
#include "Algorithm.h"
#include <mutex>

class RateLimiter
{
private:
    IRateLimitStrategy* strategy;

    int totalRequests;
    int allowedRequests;
    int rejectedRequests;
    mutable std::mutex metricsMutex;

public:
    RateLimiter(Algorithm algorithm, int maxRequests, int windowSize);

    bool allowRequest(const std::string& userId);

    int getTotalRequests() const;
    int getAllowedRequests() const;
    int getRejectedRequests() const;
    static Algorithm selectAlgorithm(int requestRate, int rejectionRate);
};