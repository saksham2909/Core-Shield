#include "RateLimitStrategyFactory.h"
#include "SlidingWindow.h"
#include "FixedWindow.h"

IRateLimitStrategy* RateLimitStrategyFactory::create(
    Algorithm algorithm,
    int maxRequests,
    int windowSize)
{
    if (algorithm == Algorithm::SlidingWindow)
        return new SlidingWindow(maxRequests, windowSize);

    if (algorithm == Algorithm::FixedWindow)
        return new FixedWindow(maxRequests, windowSize);

    return nullptr;
}