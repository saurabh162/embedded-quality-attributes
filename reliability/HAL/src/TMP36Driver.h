#pragma once

#include "ITemperatureSensor.h"

class TMP36Driver : public ITemperatureSensor
{
public:
    float readTemperature() override
    {
        // Simulated temperature reading
        return 25.5f;
    }
};