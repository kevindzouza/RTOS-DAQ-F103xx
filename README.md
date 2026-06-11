
# RTOS Sensor Logger on STM32F103

## Overview

This project implements a real-time sensor logging system on the STM32F103 ("Blue Pill") using FreeRTOS through the CMSIS-RTOS2 API.

The system periodically acquires data from an MPU6050 IMU over I2C, transfers sensor samples between tasks using a message queue, streams telemetry over UART to a host PC, and monitors task health using a software watchdog mechanism.

The project was built to demonstrate practical RTOS concepts commonly used in embedded and firmware development, including task scheduling, inter-task communication, synchronization primitives, and fault detection.

---

## Hardware Used

* STM32F103C8T6 (Blue Pill)
* MPU6050 6-axis IMU
* ST-Link V2 Debugger
* USB-to-TTL UART Converter
* Breadboard and jumper wiring

---

## Software Stack

* STM32 HAL
* FreeRTOS
* CMSIS-RTOS2 API
* STM32CubeIDE
* GCC ARM Embedded Toolchain

---

## RTOS Concepts Demonstrated

### Task Creation and Scheduling

The application is divided into independent RTOS tasks:

#### Sensor Task

* Highest priority task
* Periodically samples the MPU6050 over I2C
* Packages sensor data into a message structure
* Pushes samples into a message queue

#### UART Monitor Task

* Receives sensor messages from the queue
* Streams telemetry over UART
* Demonstrates producer-consumer task architecture

#### Watchdog Task

* Monitors system health using a heartbeat mechanism
* Detects stalled or unresponsive tasks
* Reports task failures over UART

---

### Inter-Task Communication

A FreeRTOS/CMSIS-RTOS2 Message Queue is used to transfer sensor samples between tasks.

This architecture decouples sensor acquisition from data transmission and prevents blocking operations in the sensor acquisition path.

```text
+----------------+
|  Sensor Task   |
+-------+--------+
        |
        | Message Queue
        v
+----------------+
| UART Task      |
+----------------+
```

Benefits:

* Thread-safe communication
* Deterministic data transfer
* Separation of responsibilities
* Improved scalability

---

### Mutex Synchronization

UART access is protected using a mutex.

Without synchronization, multiple tasks attempting UART transmission simultaneously could corrupt serial output.

The mutex guarantees exclusive UART access:

```text
Task A ----\
            > UART Mutex -> UART Peripheral
Task B ----/
```

Concepts demonstrated:

* Resource protection
* Mutual exclusion
* Synchronization between tasks

---

### Software Watchdog

The watchdog task implements a heartbeat monitoring system.

The sensor task periodically updates a heartbeat flag.

The watchdog verifies that the heartbeat continues to change within an expected time window.

If the heartbeat is not updated:

```text
SensorTask heartbeat missed
```

is reported over UART.

Concepts demonstrated:

* Task health monitoring
* Fault detection
* Recovery infrastructure
* Runtime diagnostics

---

## System Architecture

```text
                   +----------------+
                   |  MPU6050 IMU   |
                   +--------+-------+
                            |
                            | I2C
                            |
                            v
                 +--------------------+
                 |    Sensor Task      |
                 |  Data Acquisition   |
                 +----------+----------+
                            |
                            | Queue
                            |
                            v
                 +--------------------+
                 |   UART Task        |
                 | Telemetry Output   |
                 +----------+---------+
                            |
                            | UART
                            |
                            v
                    Host PC Terminal
                            ^
                            |
                 +----------+---------+
                 |  Watchdog Task     |
                 | Heartbeat Monitor  |
                 +--------------------+
```

---

## Sensor Data

The system collects:

### Accelerometer

* X-axis acceleration
* Y-axis acceleration
* Z-axis acceleration

### Gyroscope

* X-axis angular velocity
* Y-axis angular velocity
* Z-axis angular velocity

### Temperature

* Internal MPU6050 temperature sensor

Example UART output:

```text
AX=-3028 AY=-1004 AZ=13196 GX=959 GY=19 GZ=0 T=4832
```

---

## Logging to PC

Telemetry is streamed continuously over UART using a USB-to-TTL converter.

The output can be captured on a host PC using tools such as:

* PuTTY
* Tera Term
* CoolTerm
* Python Serial Scripts

The streamed data can be redirected and stored as CSV for further analysis and visualization.

---

## Skills Demonstrated

* Embedded C
* STM32 HAL
* FreeRTOS
* CMSIS-RTOS2
* I2C Communication
* UART Communication
* Task Scheduling
* Message Queues
* Mutexes
* Software Watchdogs
* Real-Time Systems Design
* Sensor Interfacing
* Embedded Debugging using ST-Link

---

## Future Improvements

* DMA-based UART transmission
* Event Flags and Thread Flags
* SD Card Data Logging
* Timestamped Sensor Data
* Runtime Statistics
* CLI-based System Monitoring
* Hardware Watchdog Integration
* Sensor Calibration Pipeline

---

## Author

Kevin Dsouza

Embedded Systems | Firmware Development | RTOS-Based System Design
