#pragma once
#include <cstdint>
#include "../src/ITemperatureSensor.h"

class MockTransientFailureSensor
    : public ITemperatureSensor
{
public:
    SensorResult readTemperature() override
    {
        ++attemptCount_;

        // First two attempts fail.
        if (attemptCount_ < 3)
        {
            return {
                false,
                0.0f,
                SensorError::Timeout
            };
        }

        // Third attempt succeeds.
        return {
            true,
            42.3f,
            SensorError::None
        };
    }

    std::uint8_t attemptCount() const
    {
        return attemptCount_;
    }

private:
    std::uint8_t attemptCount_{0};
};
