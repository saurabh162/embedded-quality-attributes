#pragma once

#include "../src/IDelay.h"

class MockDelay : public IDelay
{
public:
    void waitMs(std::uint32_t milliseconds) override
    {
        lastDelayMs_ = milliseconds;
        ++callCount_;
    }

    std::uint32_t callCount() const
    {
        return callCount_;
    }

    std::uint32_t lastDelayMs() const
    {
        return lastDelayMs_;
    }

private:
    std::uint32_t lastDelayMs_{0};
    std::uint32_t callCount_{0};
};