#include "TemperatureSensorService.h"

TemperatureSensorService::TemperatureSensorService(
    ITemperatureSensor& sensor,
    IDelay& delay,
    RetryPolicy retryPolicy)
    : sensor_(sensor),
      delay_(delay),
      retryPolicy_(retryPolicy)
{
}

SensorResult TemperatureSensorService::readTemperature()
{
    SensorResult result{
        false,
        0.0f,
        SensorError::HardwareFault
    };

    for (std::uint8_t attempt = 1;
         attempt <= retryPolicy_.maxAttempts;
         ++attempt)
    {
        result = sensor_.readTemperature();

        // Operation succeeded.
        if (result.success)
        {
            return result;
        }

        // Do not retry permanent/non-retryable failures.
        if (!isRetryable(result.error))
        {
            return result;
        }

        // Retry only if another attempt remains.
        if (attempt < retryPolicy_.maxAttempts)
        {
            delay_.waitMs(retryPolicy_.delayMs);
        }
    }

    // Retry budget exhausted.
    return result;
}

bool TemperatureSensorService::isRetryable(
    SensorError error) const
{
    switch (error)
    {
        case SensorError::Timeout:
        case SensorError::Busy:
        case SensorError::CommunicationError:
            return true;

        case SensorError::None:
        case SensorError::InvalidData:
        case SensorError::HardwareFault:
            return false;
    }

    return false;
}