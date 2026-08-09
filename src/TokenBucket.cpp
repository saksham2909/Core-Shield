#include "TokenBucket.h"


TokenBucket::TokenBucket(int capacity, double refillRate)
    : capacity(capacity), refillRate(refillRate)
{
}

bool TokenBucket::allowRequest(const std::string& userId)
{
    long long currentTime =
        std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();

    auto& bucket = users[userId];

    if (bucket.lastRefill == 0)
    {
        bucket.tokens = capacity;
        bucket.lastRefill = currentTime;
    }

    double elapsed = currentTime - bucket.lastRefill;
    bucket.tokens = std::min(
        (double)capacity,
        bucket.tokens + elapsed * refillRate
    );

    bucket.lastRefill = currentTime;

    if (bucket.tokens < 1)
        return false;

    bucket.tokens--;

    return true;
}