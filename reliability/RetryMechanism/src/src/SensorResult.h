#pragma once

#include "SensorError.h"

struct SensorResult
{
    bool success;
    float temperature;
    SensorError error;
};