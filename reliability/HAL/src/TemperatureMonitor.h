#pragma once

#include <iostream>

#include "ITemperatureSensor.h"

class TemperatureMonitor
{
public:
    explicit TemperatureMonitor(ITemperatureSensor& sensor)
        : sensor_(sensor)
    {
    }

    void monitor()
    {
        float temperature = sensor_.readTemperature();

        std::cout << "Temperature: "
                  << temperature
                  << " °C"
                  << std::endl;

        if (temperature > 80.0f)
        {
            std::cout << "Alarm Triggered!"
                      << std::endl;
        }
    }

private:
    ITemperatureSensor& sensor_;
};