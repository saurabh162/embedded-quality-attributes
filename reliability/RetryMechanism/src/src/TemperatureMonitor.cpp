#include "TemperatureMonitor.h"

#include <iostream>

TemperatureMonitor::TemperatureMonitor(
    TemperatureSensorService& sensorService)
    : sensorService_(sensorService)
{
}

void TemperatureMonitor::monitor()
{
    SensorResult result =
        sensorService_.readTemperature();

    if (!result.success)
    {
        handleSensorFailure(result.error);
        return;
    }

    std::cout
        << "Temperature: "
        << result.temperature
        << " C"
        << std::endl;

    if (result.temperature > 80.0f)
    {
        std::cout
            << "Alarm Triggered!"
            << std::endl;
    }
}

void TemperatureMonitor::handleSensorFailure(
    SensorError error)
{
    std::cout
        << "Temperature measurement unavailable."
        << std::endl;

    // Higher-level failure handling could:
    //
    // - raise a diagnostic event
    // - mark the sensor unavailable
    // - notify the operator
    // - enter degraded mode
    // - request system-level recovery

    (void)error;
}