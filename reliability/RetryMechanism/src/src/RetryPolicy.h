#pragma once

struct RetryPolicy
{
    std::uint8_t maxAttempts;
    std::uint32_t delayMs;
};