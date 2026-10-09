#pragma once

#include "TemperatureSensorService.h"

class TemperatureMonitor
{
public:
    explicit TemperatureMonitor(
        TemperatureSensorService& sensorService);

    void monitor();

private:
    void handleSensorFailure(SensorError error);

    TemperatureSensorService& sensorService_;
};