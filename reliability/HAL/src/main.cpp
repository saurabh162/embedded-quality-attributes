#include "MockTemperatureSensor.h"
#include "TMP36Driver.h"
#include "TemperatureMonitor.h"

int main()
{
    // Real hardware driver
    TMP36Driver realSensor;
    TemperatureMonitor monitor(realSensor);

    monitor.monitor();

    // Mock sensor used for testing
    MockTemperatureSensor mockSensor(95.0f);
    TemperatureMonitor testMonitor(mockSensor);

    testMonitor.monitor();

    return 0;
}