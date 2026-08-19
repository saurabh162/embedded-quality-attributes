# Hardware Abstraction Layer (HAL)
## Contents

- [Real Problem](#real-problem)
- [Why It Happens](#why-it-happens)
- [Architecture Solution](#architecture-solution)
- [UML Diagram](#uml-diagram)
- [CPP EXAMPLE](#cpp-example)
- [Benefits](#benefits)
- [Tradeoffs](#tradeoffs)
   
---

## Real Problem

### Problem Description

Imagine we are developing a **Temperature Monitoring Device**.

The device has three main responsibilities:

- Read temperature from a sensor
- Display temperature to the operator
- Send temperature measurements to a supervisory system

Initially, the system uses a **TMP36 temperature sensor**. The application directly communicates with the TMP36 driver to obtain temperature readings.

### Initial Design

```mermaid
graph TD
    A[Temperature Monitor] --> B[TMP36 Driver]
    B --> C[Hardware]
```

At first glance, this design looks simple and works correctly.

However, after deployment, several situations may occur:

- TMP36 sensor becomes obsolete
- Customer requests a different sensor
- New hardware platform is selected
- Software team wants to perform unit testing on a PC
- Engineers want to simulate sensor failures
- Production team finds a hardware-related bug

### Example Scenario

Assume the monitoring application contains code like this:

```cpp
float temperature = tmp36Driver.readTemperature();
```
A year later, marketing decides to replace TMP36 with a digital sensor such as TMP117.

Now every module that directly uses `tmp36Driver` must be modified and retested.

Even a small hardware change can create:

- Additional development effort
- Higher regression testing cost
- Increased risk of software defects
- Longer release cycles

### Impact on Reliability

Direct hardware dependency reduces system reliability because:

#### 1. Difficult Fault Injection

It becomes hard to simulate:

- Sensor disconnection
- Invalid readings
- Noise
- Hardware failures

Without simulation capability, many failure scenarios remain untested.

#### 2. Limited Unit Testing

Application code cannot easily run without actual hardware.

Developers often need:

- Evaluation boards
- Hardware setups
- Real sensors

for even basic testing.

#### 3. High Change Impact

A sensor replacement may force changes across multiple software modules.

More modified code means:

- More regression testing
- Higher defect probability
- Lower maintainability

#### 4. Tight Coupling

Application logic becomes tightly coupled to the hardware implementation.

When one side changes, the other side is often affected.

### Reliability Risk Summary

| Risk | Effect |
|--------|----------|
| Sensor replacement | Application modifications required |
| New MCU platform | Driver and application updates |
| Hardware fault simulation | Difficult |
| Unit testing | Hardware dependent |
| Maintenance effort | High |
| Regression risk | High |


## Why It Happens 

### Root Cause

The problem occurs because the application depends directly on a specific hardware implementation.

In our example, the `TemperatureMonitor` communicates directly with the `TMP36 Driver`.

```mermaid
graph TD
    A[Temperature Monitor] --> B[TMP36 Driver]
    B --> C[Hardware]
```

The application knows exactly:

- Which sensor is being used
- Which driver is being used
- How the hardware is accessed

This creates a strong dependency between the application and the hardware.

This problem is what motivates the introduction of a **Hardware Abstraction Layer (HAL)**.

## Architecture Solution 

### Solution Overview

The root cause of the problem is that the application depends directly on a specific hardware driver.

```mermaid
graph TD
    A[Temperature Monitor] --> B[TMP36 Driver]
    B --> C[Hardware]
```

As a result:

- Hardware changes affect application code.
- Unit testing becomes difficult.
- Fault simulation becomes difficult.
- Software reuse is limited.

To solve this problem, we introduce a **Hardware Abstraction Layer (HAL)**.

---

### What Is a Hardware Abstraction Layer (HAL)?

A Hardware Abstraction Layer (HAL) is a software layer that sits between:

- Application logic
- Hardware-specific drivers

The application communicates with an abstraction instead of a concrete driver.

```mermaid
graph TD
    A[Application] --> B[HAL]
    B --> C[Hardware Driver]
    C --> D[Hardware]
```

This separation prevents hardware details from leaking into the application layer.

---

### Applying HAL to Our Temperature Monitoring Device

Instead of directly using the `TMP36Driver`, the application depends on an interface called `ITemperatureSensor`.

```mermaid
flowchart TD

    TM[Temperature Monitor]
    ITS[ITemperatureSensor]
    TMP[TMP36 Driver]

    TM --> ITS
    ITS --> TMP
```

The application no longer knows anything about:

- TMP36
- TMP117
- ADC implementation
- MCU registers

The application only knows:

> "I need a temperature value."

---

### Introducing an Interface

The HAL can be represented by an interface:

```cpp
class ITemperatureSensor
{
public:
    virtual float readTemperature() = 0;
    virtual ~ITemperatureSensor() = default;
};
```

This interface defines **what** the application needs.

It does not define **how** the temperature is obtained.

---

### Hardware-Specific Drivers Implement the Interface

The actual driver provides the implementation.

```cpp
class TMP36Driver : public ITemperatureSensor
{
public:
    float readTemperature() override;
};
```

Future sensors can also implement the same interface.

```cpp
class TMP117Driver : public ITemperatureSensor
{
public:
    float readTemperature() override;
};
```

Both drivers provide the same functionality to the application.

---

### Dependency Direction Changes

Before HAL:

```mermaid
graph TD
    TM[TemperatureMonitor] --> TMP[TMP36 Driver]
```

After HAL:

```mermaid
graph TD
    TM[Temperature Monitor]
    ITS[ITemperatureSensor]
    TMP[TMP36 Driver]

    TM --> ITS
    TMP --> ITS
```

This is an important architectural improvement.

The application now depends on an abstraction rather than a concrete implementation.

---

### Testing Becomes Easier

A mock implementation can be created for unit testing.

```cpp
class MockTemperatureSensor : public ITemperatureSensor
{
public:
    float readTemperature() override
    {
        return 95.0f;
    }
};
```

Now application logic can be tested without:

- Real hardware
- Development boards
- Physical sensors

This significantly improves testability.

---

### Sensor Replacement Becomes Simpler

Suppose the TMP36 sensor is replaced by a TMP117.

Without HAL:

```text
Application changes
        +
Driver changes
```

With HAL:

```text
Application unchanged
        +
Driver changes
```

Only the hardware-specific implementation needs modification.

The business logic remains untouched.

---

### Fault Simulation Becomes Possible

Mock implementations can simulate:

- Sensor failures
- Invalid measurements
- Extreme temperatures
- Communication errors
- Timeout conditions

This allows reliability scenarios to be tested long before hardware is available.

---

### How HAL Improves Reliability

The HAL pattern improves reliability by:

- Reducing coupling between software and hardware
- Simplifying hardware replacement
- Supporting fault injection testing
- Enabling unit testing without hardware
- Isolating hardware-specific changes
- Increasing code reuse across projects

---

### Key Takeaway

The Hardware Abstraction Layer (HAL) separates application logic from hardware-specific implementation details.

Instead of depending on a concrete driver such as `TMP36Driver`, the application depends on an abstraction (`ITemperatureSensor`).

This simple architectural change makes the system:

- More maintainable
- More testable
- More reusable
- More resilient to hardware changes

In the next section, we will visualize this design using a UML Class Diagram.

## UML Diagram 

### Purpose of the Diagram

The UML Class Diagram visualizes how the Hardware Abstraction Layer (HAL) separates the application from hardware-specific implementations.

Instead of depending directly on a concrete driver, the application depends on an abstraction (`ITemperatureSensor`).

This enables:

- Easier hardware replacement
- Improved testability
- Better maintainability
- Fault simulation through mock implementations

---

### UML Class Diagram

```mermaid
classDiagram

    class TemperatureMonitor
    class ITemperatureSensor
    class TMP36Driver
    class MockTemperatureSensor

    TemperatureMonitor --> ITemperatureSensor : uses

    TMP36Driver ..|> ITemperatureSensor : implements
    MockTemperatureSensor ..|> ITemperatureSensor : implements
```

---

### Diagram Explanation

#### TemperatureMonitor

The `TemperatureMonitor` class contains the application logic.

Responsibilities:

- Obtain temperature measurements
- Process temperature values
- Trigger alarms or notifications
- Send data to other system components

Most importantly, it does **not** know which sensor is being used.

It only depends on the `ITemperatureSensor` interface.

---

#### ITemperatureSensor

The `ITemperatureSensor` interface represents the Hardware Abstraction Layer (HAL).

Example:

```cpp
class ITemperatureSensor
{
public:
    virtual float readTemperature() = 0;
    virtual ~ITemperatureSensor() = default;
};
```

The interface defines:

> "What the application needs"

instead of

> "How the hardware works"

This allows the application to remain independent of hardware details.

---

#### TMP36Driver

`TMP36Driver` is a hardware-specific implementation of the interface.

Responsibilities:

- Read ADC values
- Convert voltage into temperature
- Interact with the underlying hardware

The application never communicates with this class directly.

---

#### MockTemperatureSensor

`MockTemperatureSensor` is used during testing.

It allows developers to:

- Run tests without hardware
- Simulate sensor failures
- Simulate extreme temperatures
- Verify application behavior

Example:

```cpp
MockTemperatureSensor mockSensor;
```

This object can return predefined values during unit testing.

---

### Dependency Flow

The dependency flow is intentionally designed as follows:

```mermaid
graph TD
    TM[TemperatureMonitor]
    ITS[ITemperatureSensor]

    TM --> ITS
    TMP36Driver --> ITS
```
``

The important observation is that:

✅ Application depends on the interface.

✅ Driver depends on the interface.

✅ Application does not depend on the driver.

This dependency direction helps isolate hardware changes from application logic.

---

### Why This Design Is More Reliable

Suppose the TMP36 sensor is replaced with a new sensor.

Without HAL:

```text
TemperatureMonitor → TMP36Driver
```

Application code may need modification.

With HAL:

```text
TemperatureMonitor → ITemperatureSensor
```

Only the new driver implementation changes.

The application remains untouched.

As a result:

- Hardware upgrades become simpler.
- Maintenance effort is reduced.
- Regression risk is lower.
- Unit testing becomes easier.

---

### Key Takeaway

The UML diagram demonstrates the core idea behind the Hardware Abstraction Layer pattern:

> Depend on abstractions, not concrete implementations.

By introducing the `ITemperatureSensor` interface, the application becomes independent of hardware-specific details, resulting in a more maintainable, testable, and reliable embedded system.

## CPP EXAMPLE

### Goal

The goal of this example is to demonstrate how a Hardware Abstraction Layer (HAL) allows the application to depend on an abstraction instead of a hardware-specific driver.

---

### Step 1: Define the HAL Interface

The application only needs a temperature value.

The interface defines *what* the application needs, not *how* the temperature is obtained.

```cpp
class ITemperatureSensor
{
public:
    virtual float readTemperature() = 0;
    virtual ~ITemperatureSensor() = default;
};
```

---

### Step 2: Implement the TMP36 Driver

The driver implements the HAL interface.

```cpp
class TMP36Driver : public ITemperatureSensor
{
public:
    float readTemperature() override
    {
        // In a real system:
        // 1. Read ADC value
        // 2. Convert voltage to temperature
        // 3. Return temperature

        return 25.5f;
    }
};
```

---

### Step 3: Create the Application Logic

The application depends only on the interface.

```cpp
#include <iostream>

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
```

Notice that `TemperatureMonitor` does not know:

- Which sensor is used
- How the sensor works
- How temperature is obtained

It only knows about the `ITemperatureSensor` interface.

---

### Step 4: Connect Everything Together

```cpp
int main()
{
    TMP36Driver sensor;

    TemperatureMonitor monitor(sensor);

    monitor.monitor();

    return 0;
}
```

Output:

```text
Temperature: 25.5 °C
```

---

### Unit Testing Without Hardware

One of the biggest benefits of HAL is that we can replace the real driver with a mock implementation.

---

### Step 5: Create a Mock Sensor

```cpp
class MockTemperatureSensor : public ITemperatureSensor
{
public:
    float readTemperature() override
    {
        return 95.0f;
    }
};
```

---

### Step 6: Test the Application

Without changing a single line inside `TemperatureMonitor`, we can test alarm behavior.

```cpp
int main()
{
    MockTemperatureSensor sensor;

    TemperatureMonitor monitor(sensor);

    monitor.monitor();

    return 0;
}
```

Output:

```text
Temperature: 95.0 °C
Alarm Triggered!
```

---

### Sensor Replacement Example

Suppose the TMP36 sensor is replaced by a TMP117 sensor.

A new driver can be written:

```cpp
class TMP117Driver : public ITemperatureSensor
{
public:
    float readTemperature() override
    {
        return 24.8f;
    }
};
```

Application code remains unchanged:

```cpp
TMP117Driver sensor;
TemperatureMonitor monitor(sensor);
```

No modifications are required in:

- TemperatureMonitor
- Alarm logic
- Business rules
- Reporting components

---

### What We Achieved

By introducing the `ITemperatureSensor` interface:

✅ Application logic is independent of hardware.

✅ Hardware can be replaced with minimal effort.

✅ Unit tests can run without real hardware.

✅ Fault scenarios can be simulated easily.

✅ Software becomes more maintainable and reusable.

---

### Key Takeaway

The application depends on the abstraction:

```text
TemperatureMonitor --> ITemperatureSensor
```

instead of the implementation:

```text
TemperatureMonitor --> TMP36Driver
```

This simple change improves testability, maintainability, and reliability while keeping the application isolated from hardware-specific details.

### Complete Source Code

The complete implementation can be found in:

```text
src/
├── ITemperatureSensor.h
├── TMP36Driver.h
├── MockTemperatureSensor.h
├── TemperatureMonitor.h
└── main.cpp
```

### Building the Example

```bash
make
```

### Running the Example

```bash
make run
```

### Cleaning Build Files

```bash
make clean
```
