#pragma once

#include "ITemperatureSensor.h"

class MockTemperatureSensor : public ITemperatureSensor
{
public:
    explicit MockTemperatureSensor(float temperature)
        : temperature_(temperature)
    {
    }

    float readTemperature() override
    {
        return temperature_;
    }

private:
    float temperature_;
};