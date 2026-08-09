#include "FixedWindow.h"
#include <chrono>

FixedWindow::FixedWindow(int maxRequests, int windowSize)
    : maxRequests(maxRequests),
      windowSize(windowSize)
{
}

bool FixedWindow::allowRequest(const std::string& userId)
{
    std::lock_guard<std::mutex> lock(mutex);

    auto now = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();

    auto& window = windows[userId];

    if (window.startTime == 0 ||
        now - window.startTime >= windowSize)
    {
        window.startTime = now;
        window.requestCount = 0;
    }

    if (window.requestCount >= maxRequests)
        return false;

    window.requestCount++;

    return true;
}