#include <cassert>
#include "RateLimiter.h"
#include "AlgorithmSelector.h"
#include <thread>
#include <vector>
#include <chrono>

void testConcurrentRequests()
{
    RateLimiter limiter(Algorithm::FixedWindow, 1000, 60);

    std::vector<std::thread> threads;

    for (int i = 0; i < 10; i++)
    {
        threads.emplace_back([&limiter]()
        {
            for (int j = 0; j < 100; j++)
                limiter.allowRequest("user1");
        });
    }

    for (auto& thread : threads)
        thread.join();

    assert(limiter.getTotalRequests() == 1000);
}

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

void testSlidingWindowExpiry()
{
    RateLimiter limiter(Algorithm::SlidingWindow, 2, 1);

    assert(limiter.allowRequest("user1"));
    assert(limiter.allowRequest("user1"));
    assert(!limiter.allowRequest("user1"));

    std::this_thread::sleep_for(std::chrono::seconds(2));

    assert(limiter.allowRequest("user1"));
}

void testFixedWindow()
{
    RateLimiter limiter(Algorithm::FixedWindow, 2, 10);

    assert(limiter.allowRequest("user1"));
    assert(limiter.allowRequest("user1"));
    assert(!limiter.allowRequest("user1"));
}

void testFixedWindowReset()
{
    RateLimiter limiter(Algorithm::FixedWindow, 2, 1);

    assert(limiter.allowRequest("user1"));
    assert(limiter.allowRequest("user1"));
    assert(!limiter.allowRequest("user1"));

    std::this_thread::sleep_for(std::chrono::seconds(2));

    assert(limiter.allowRequest("user1"));
}

void testTokenBucket()
{
    RateLimiter limiter(Algorithm::TokenBucket, 2, 1);

    assert(limiter.allowRequest("user1"));
    assert(limiter.allowRequest("user1"));
    assert(!limiter.allowRequest("user1"));
}

void testTokenBucketRefill()
{
    RateLimiter limiter(Algorithm::TokenBucket, 2, 1);

    assert(limiter.allowRequest("user1"));
    assert(limiter.allowRequest("user1"));
    assert(!limiter.allowRequest("user1"));

    std::this_thread::sleep_for(std::chrono::milliseconds(1100));

    assert(limiter.allowRequest("user1"));
}

void testMultipleUsers()
{
    RateLimiter limiter(Algorithm::SlidingWindow, 1, 10);

    assert(limiter.allowRequest("user1"));
    assert(!limiter.allowRequest("user1"));

    assert(limiter.allowRequest("user2"));
}

void testConcurrentAlgorithms()
{
    std::vector<Algorithm> algorithms =
    {
        Algorithm::SlidingWindow,
        Algorithm::FixedWindow,
        Algorithm::TokenBucket
    };

    for (Algorithm algorithm : algorithms)
    {
        RateLimiter limiter(algorithm, 1000, 60);

        std::vector<std::thread> threads;

        for (int i = 0; i < 10; i++)
        {
            threads.emplace_back([&limiter]()
            {
                for (int j = 0; j < 100; j++)
                    limiter.allowRequest("user1");
            });
        }

        for (auto& thread : threads)
            thread.join();

        assert(limiter.getTotalRequests() == 1000);
    }
}

int main()
{
    testSlidingWindow();
    testSlidingWindowExpiry();

    testFixedWindow();
    testFixedWindowReset();

    testTokenBucket();
    testTokenBucketRefill();

    testMultipleUsers();
    testAlgorithmSelector();
    testConcurrentRequests();
    testConcurrentAlgorithms();

    return 0;
}