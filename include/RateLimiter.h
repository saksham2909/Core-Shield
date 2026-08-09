#pragma once

#include <string>
#include "1_RateLimitStrategy.h"
#include "Algorithm.h"

class RateLimiter
{
private:
    IRateLimitStrategy* strategy;

    int totalRequests;
    int allowedRequests;
    int rejectedRequests;

public:
    RateLimiter(Algorithm algorithm, int maxRequests, int windowSize);

    bool allowRequest(const std::string& userId);

    int getTotalRequests() const;
    int getAllowedRequests() const;
    int getRejectedRequests() const;
    static Algorithm selectAlgorithm(int requestRate, int rejectionRate);
};