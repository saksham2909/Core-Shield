#include <iostream>
#include "RateLimiter.h"

int main()
{
    RateLimiter limiter(Algorithm::TokenBucket, 3, 1);

    std::string userId = "api-user";

    for (int i = 1; i <= 5; i++)
    {
        if (limiter.allowRequest(userId))
            std::cout << "API request " << i << " allowed\n";
        else
            std::cout << "API request " << i << " rejected\n";
    }

    return 0;
}