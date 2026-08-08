#include "FixedWindow.h"

FixedWindow::FixedWindow(int maxRequests, int windowSize)
    : maxRequests(maxRequests), windowSize(windowSize)
{
}

bool FixedWindow::allowRequest(const std::string& userId)
{
    long long currentTime =
        std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();

    auto& window = users[userId];

    if (currentTime - window.startTime >= windowSize)
    {
        window.startTime = currentTime;
        window.requestCount = 0;
    }

    if (window.requestCount >= maxRequests)
        return false;

    window.requestCount++;

    return true;
}