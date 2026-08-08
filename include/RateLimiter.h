#pragma once

#include <string>
#include "1_RateLimitStrategy.h"
#include "Algorithm.h"

class RateLimiter
{
private:
    IRateLimitStrategy* strategy;

public:
    RateLimiter(Algorithm algorithm, int maxRequests, int windowSize);

    bool allowRequest(const std::string& userId);
};