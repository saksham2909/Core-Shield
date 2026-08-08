#include <iostream>
#include "RateLimiter.h"

int main()
{
    RateLimiter limiter(
        Algorithm::SlidingWindow,
        3,
        10
    );

    std::cout << limiter.allowRequest("user123") << "\n";
    std::cout << limiter.allowRequest("user123") << "\n";
    std::cout << limiter.allowRequest("user123") << "\n";
    std::cout << limiter.allowRequest("user123") << "\n";

    return 0;
}