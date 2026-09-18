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

In the previous design, we introduced a **Hardware Abstraction Layer (HAL)** to isolate the `TemperatureMonitor` from the concrete temperature sensor.

Our architecture now looks approximately like this:

```mermaid
flowchart TB
    TM[TemperatureMonitor] --> ITS[ITemperatureSensor]
    TMP[TMP36 Driver] --> ITS

This solved an important architectural problem:

The application no longer depends directly on a specific sensor implementation.

But abstraction does not make hardware failures disappear.

Consider our **industrial temperature monitoring device**.

The system periodically:

- Reads the temperature sensor
- Processes the measurement
- Displays the temperature to the operator
- Reports the measurement to a supervisory system

During normal operation, a sensor read might occasionally fail.

For example:

```text
Read #1 → Communication Timeout
Read #2 → 42.3 °C
Read #3 → 42.4 °C
```

The first operation failed, but the sensor itself was not permanently broken.

The failure was **transient**.



### Two Naive Reactions

## Why It Happens 

### Root Cause

### Transient vs Persistent Failure

## Architecture Solution 

### Introduce a Bounded Retry Policy
### Retry Should Be Selective
### Where Should Retry Live? 
### Retry Must Be Bounded  
### Retry Has a Timing Cost

## UML Diagram 

### Purpose of the Diagram
### UML Class Diagram
### Diagram Explanation


## CPP EXAMPLE
### Goal




## Benefits 

## Tradeoffs 

### Trade-off Summary

### Key Takeaway

