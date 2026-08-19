#include <iostream>
#include "RateLimiter.h"

int main()
{
    RateLimiter limiter(Algorithm::FixedWindow, 3, 10);

    for (int i = 1; i <= 5; i++)
    {
        if (limiter.allowRequest("external-user"))
            std::cout << "Allowed\n";
        else
            std::cout << "Rejected\n";
    }

    return 0;
}