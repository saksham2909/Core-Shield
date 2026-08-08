#include "RateLimiter.h"
#include "RateLimitStrategyFactory.h"

RateLimiter::RateLimiter(
    Algorithm algorithm,
    int maxRequests,
    int windowSize)
{
    strategy = RateLimitStrategyFactory::create(
        algorithm,
        maxRequests,
        windowSize
    );
}

bool RateLimiter::allowRequest(const std::string& userId)
{
    return strategy->allowRequest(userId);
}