#pragma once

#include <cstdint>

class IDelay
{
public:
    virtual void waitMs(std::uint32_t milliseconds) = 0;

    virtual ~IDelay() = default;
};