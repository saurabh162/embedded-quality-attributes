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
