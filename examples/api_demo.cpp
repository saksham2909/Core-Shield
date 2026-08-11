#include <iostream>
#include "RateLimiter.h"

int main()
{
    RateLimiter limiter(Algorithm::TokenBucket, 5, 10);

    for (int i = 1; i <= 10; i++)
    {
        bool allowed = limiter.allowRequest("user123");

        std::cout << "Request " << i << ": "
                  << (allowed ? "Allowed" : "Rejected")
                  << "\n";
    }

    std::cout << "\nTotal Requests: "
              << limiter.getTotalRequests() << "\n";

    std::cout << "Allowed Requests: "
              << limiter.getAllowedRequests() << "\n";

    std::cout << "Rejected Requests: "
              << limiter.getRejectedRequests() << "\n";

    return 0;
}