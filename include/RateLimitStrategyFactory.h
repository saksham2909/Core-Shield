#pragma once

#include "IRateLimitStrategy.h"
#include "Algorithm.h"

class RateLimitStrategyFactory
{
public:
    static IRateLimitStrategy* create(
        Algorithm algorithm,
        int maxRequests,
        int windowSize
    );
};