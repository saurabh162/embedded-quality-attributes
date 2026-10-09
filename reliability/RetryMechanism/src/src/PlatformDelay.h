#pragma once

#include "IDelay.h"

class PlatformDelay : public IDelay
{
public:
    void waitMs(std::uint32_t milliseconds) override
    {
        // Replace with target-specific implementation:
        //
        // HAL_Delay(...)
        // vTaskDelay(...)
        // osDelay(...)
        // hardware timer
        // etc.

        (void)milliseconds;
    }
};
