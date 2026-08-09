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
    bool allowed = strategy->allowRequest(userId);

    std::lock_guard<std::mutex> lock(metricsMutex);

    totalRequests++;

    if (allowed)
        allowedRequests++;
    else
        rejectedRequests++;

    return allowed;
}

int RateLimiter::getTotalRequests() const
{
    std::lock_guard<std::mutex> lock(metricsMutex);
    return totalRequests;
}

int RateLimiter::getAllowedRequests() const
{
    std::lock_guard<std::mutex> lock(metricsMutex);
    return allowedRequests;
}

int RateLimiter::getRejectedRequests() const
{
    std::lock_guard<std::mutex> lock(metricsMutex);
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