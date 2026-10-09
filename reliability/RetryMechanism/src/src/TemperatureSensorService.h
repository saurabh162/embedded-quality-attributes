#pragma once

#include "ITemperatureSensor.h"
#include "IDelay.h"
#include "RetryPolicy.h"

class TemperatureSensorService
{
public:
    TemperatureSensorService(
        ITemperatureSensor& sensor,
        IDelay& delay,
        RetryPolicy retryPolicy);

    SensorResult readTemperature();

private:
    bool isRetryable(SensorError error) const;

    ITemperatureSensor& sensor_;
    IDelay& delay_;
    RetryPolicy retryPolicy_;
};