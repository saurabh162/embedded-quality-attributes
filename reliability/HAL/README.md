# Hardware Abstraction Layer (HAL)

## 1. Real Problem 🚨

## 2. Why It Happens 🔍

## 3. Architecture Solution 🏛️

## 4. UML Diagram 📐

## 5. C++ Example 💻

## 6. Benefits ✅

## 7. Trade-offs ⚖️

## 1. Real Problem 🚨

### Problem Description

Imagine we are developing a **Temperature Monitoring Device**.

The device has three main responsibilities:

- Read temperature from a sensor
- Display temperature to the operator
- Send temperature measurements to a supervisory system

Initially, the system uses a **TMP36 temperature sensor**. The application directly communicates with the TMP36 driver to obtain temperature readings. 【1-fe0023】

### Initial Design

```text
+--------------------+
| TemperatureMonitor |
+--------------------+
          |
          v
+--------------------+
|    TMP36 Driver    |
+--------------------+
          |
          v
+--------------------+
|      Hardware      |
+--------------------+

At first glance, this design looks simple and works correctly.

However, after deployment, several situations may occur:

- TMP36 sensor becomes obsolete
- Customer requests a different sensor
- New hardware platform is selected
- Software team wants to perform unit testing on a PC
- Engineers want to simulate sensor failures
- Production team finds a hardware-related bug

All of these changes directly affect the application because it depends on a specific hardware driver.

## Example Scenario

Assume the monitoring application contains code like this:
