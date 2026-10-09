#pragma once

#include "../src/ITemperatureSensor.h"

class MockHardwareFailureSensor
    : public ITemperatureSensor
{
public:
    SensorResult readTemperature() override
    {
        ++attemptCount_;

        return {
            false,
            0.0f,
            SensorError::HardwareFault
        };
    }

    std::uint8_t attemptCount() const
    {
        return attemptCount_;
    }

private:
    std::uint8_t attemptCount_{0};
};