#pragma once

#include "ITemperatureSensor.h"

class TMP36Driver : public ITemperatureSensor
{
public:
    SensorResult readTemperature() override
    {
        // Real implementation would:
        //
        // 1. Start ADC conversion
        // 2. Wait for conversion or timeout
        // 3. Read ADC value
        // 4. Convert voltage to temperature
        // 5. Return success or appropriate error

        return {
            true,
            25.5f,
            SensorError::None
        };
    }
};