#include <iostream>
#include <chrono>
#include "RateLimiter.h"

void runTest(
    Algorithm algorithm,
    const std::string& name,
    const std::string& workload,
    int requests,
    int limit)
{
    RateLimiter limiter(algorithm, limit, 60);

    int allowed = 0;
    int rejected = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < requests; i++)
    {
        if (limiter.allowRequest("user1"))
            allowed++;
        else
            rejected++;
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto time =
        std::chrono::duration_cast<std::chrono::microseconds>(
            end - start
        ).count();

    std::cout << workload << " | "
              << name << " | "
              << "Allowed: " << allowed << " | "
              << "Rejected: " << rejected << " | "
              << "Time: " << time << " us\n";
}

void benchmark(
    const std::string& workload,
    int requests,
    int limit)
{
    runTest(Algorithm::SlidingWindow, "Sliding Window",
            workload, requests, limit);

    runTest(Algorithm::FixedWindow, "Fixed Window",
            workload, requests, limit);

    runTest(Algorithm::TokenBucket, "Token Bucket",
            workload, requests, limit);
}

int main()
{
    benchmark("Steady Load", 100000, 100000);
    benchmark("Burst Load", 100000, 1000);
    benchmark("High Rejection", 100000, 100);

    return 0;
}