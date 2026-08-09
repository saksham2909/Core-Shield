#include <cassert>
#include "RateLimiter.h"
#include "AlgorithmSelector.h"
void testAlgorithmSelector()
{
    assert(
        RateLimiter::selectAlgorithm(2000, 10)
        == Algorithm::FixedWindow
    );

    assert(
        RateLimiter::selectAlgorithm(500, 60)
        == Algorithm::TokenBucket
    );

    assert(
        RateLimiter::selectAlgorithm(500, 10)
        == Algorithm::SlidingWindow
    );
}

void testSlidingWindow()
{
    RateLimiter limiter(Algorithm::SlidingWindow, 2, 10);

    assert(limiter.allowRequest("user1"));
    assert(limiter.allowRequest("user1"));
    assert(!limiter.allowRequest("user1"));
}

void testFixedWindow()
{
    RateLimiter limiter(Algorithm::FixedWindow, 2, 10);

    assert(limiter.allowRequest("user1"));
    assert(limiter.allowRequest("user1"));
    assert(!limiter.allowRequest("user1"));
}

void testTokenBucket()
{
    RateLimiter limiter(Algorithm::TokenBucket, 2, 1);

    assert(limiter.allowRequest("user1"));
    assert(limiter.allowRequest("user1"));
    assert(!limiter.allowRequest("user1"));
}

void testMultipleUsers()
{
    RateLimiter limiter(Algorithm::SlidingWindow, 1, 10);

    assert(limiter.allowRequest("user1"));
    assert(!limiter.allowRequest("user1"));

    assert(limiter.allowRequest("user2"));
}

int main()
{
    testSlidingWindow();
    testFixedWindow();
    testTokenBucket();
    testMultipleUsers();
    testAlgorithmSelector();

    return 0;
}