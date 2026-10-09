#include "TMP36Driver.h"
#include "../tests/MockTransientFailureSensor.h" // To test transistent failure 
#include "../tests/MockPersistentFailureSensor.h" // To test persistent failure 
#include "../tests/MockHardwareFailureSensor.h" // To test hardware  failure
#include "PlatformDelay.h"
#include "RetryPolicy.h"
#include "TemperatureSensorService.h"
#include "TemperatureMonitor.h"

int main()
{
     TMP36Driver sensor;
    // MockTransientFailureSensor sensor;  // To test transient failure 
    // MockPersistentFailureSensor sensor; // To test Persistent Failure
    // MockHardwareFailureSensor sensor;
    PlatformDelay delay;

    RetryPolicy retryPolicy{
        3,      // Maximum total attempts
        10      // Delay between attempts in ms
    };

    TemperatureSensorService sensorService(
        sensor,
        delay,
        retryPolicy);

    TemperatureMonitor monitor(
        sensorService);

    monitor.monitor();

    return 0;
}
