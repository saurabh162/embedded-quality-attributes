#pragma once

#include "SensorResult.h"

class ITemperatureSensor
{
public:
    virtual SensorResult readTemperature() = 0;

    virtual ~ITemperatureSensor() = default;
};