#pragma once

enum class SensorError
{
    None,
    Timeout,
    Busy,
    CommunicationError,
    InvalidData,
    HardwareFault
};