#include "SlidingWindow.h"
#include <chrono>

SlidingWindow::SlidingWindow(int maxRequests, int windowSize)
    : maxRequests(maxRequests),
      windowSize(windowSize)
{
}

bool SlidingWindow::allowRequest(const std::string& userId)
{
    std::lock_guard<std::mutex> lock(mutex);

    auto now = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();

    auto& userRequests = requests[userId];

    while (!userRequests.empty() &&
           now - userRequests.front() >= windowSize)
    {
        userRequests.pop_front();
    }

    if (userRequests.size() >= maxRequests)
        return false;

    userRequests.push_back(now);

    return true;
}