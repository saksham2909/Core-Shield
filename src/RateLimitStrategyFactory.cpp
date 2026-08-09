#include "RateLimitStrategyFactory.h"
#include "SlidingWindow.h"
#include "FixedWindow.h"
#include "TokenBucket.h"

IRateLimitStrategy* RateLimitStrategyFactory::create(
    Algorithm algorithm,
    int maxRequests,
    int windowSize)
{
    if (algorithm == Algorithm::SlidingWindow)
        return new SlidingWindow(maxRequests, windowSize);

    if (algorithm == Algorithm::FixedWindow)
        return new FixedWindow(maxRequests, windowSize);
        
    if (algorithm == Algorithm::TokenBucket)
    return new TokenBucket(maxRequests, windowSize);

    return nullptr;
}