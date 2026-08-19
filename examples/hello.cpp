#include <iostream>
#include "RateLimiter.h"

int main()
{
    RateLimiter limiter(Algorithm::SlidingWindow, 5, 60);

    for (int i = 1; i <= 7; i++)
    {
        if (limiter.allowRequest("user1"))
            std::cout << "Request " << i << " allowed\n";
        else
            std::cout << "Request " << i << " rejected\n";
    }

    return 0;
}