#pragma once

class ITemperatureSensor
{
public:
    virtual ~ITemperatureSensor() = default;

    virtual float readTemperature() = 0;
};