#pragma once

#include <string>

class IRateLimitStrategy
{
public:
    virtual bool allowRequest(const std::string& userId) = 0;
    virtual ~IRateLimitStrategy() = default;
};