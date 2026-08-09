#include "RateLimiter.h"
#include "RateLimitStrategyFactory.h"
#include "AlgorithmSelector.h"

RateLimiter::RateLimiter(
    Algorithm algorithm,
    int maxRequests,
    int windowSize)
    : totalRequests(0),
      allowedRequests(0),
      rejectedRequests(0)
{
    strategy = RateLimitStrategyFactory::create(
        algorithm,
        maxRequests,
        windowSize
    );
}

bool RateLimiter::allowRequest(const std::string& userId)
{
    totalRequests++;

    if (strategy->allowRequest(userId))
    {
        allowedRequests++;
        return true;
    }

    rejectedRequests++;
    return false;
}

int RateLimiter::getTotalRequests() const
{
    return totalRequests;
}

int RateLimiter::getAllowedRequests() const
{
    return allowedRequests;
}

int RateLimiter::getRejectedRequests() const
{
    return rejectedRequests;
}

Algorithm RateLimiter::selectAlgorithm(
    int requestRate,
    int rejectionRate)
{
    return AlgorithmSelector::select(
        requestRate,
        rejectionRate
    );
}