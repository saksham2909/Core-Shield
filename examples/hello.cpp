#include <iostream>
#include "RateLimiter.h"

int main()
{
    RateLimiter limiter(
    Algorithm::TokenBucket,
    3,
    1
);

    std::cout << limiter.allowRequest("user123") << "\n";
    std::cout << limiter.allowRequest("user123") << "\n";
    std::cout << limiter.allowRequest("user123") << "\n";
    std::cout << limiter.allowRequest("user123") << "\n";
    std::cout << limiter.allowRequest("user123") << "\n";


    return 0;
}