 Quadcopter Project: Advanced Movement Control

## Introduction

This document details the advanced movement control system implemented in the Quadcopter Project, focusing on the use of a cascading PID (Proportional-Integral-Derivative) control system to manage the pitch, roll, and yaw movements. The integration of these technologies ensures precise and responsive maneuvering of the quadcopter.

## Quadcopter Layout and Components

### ESP32 and Control System
- Central to the quadcopter's control system is the **ESP32** microcontroller.
- It acts as the brain of the quadcopter, processing inputs and managing communication.

### Electronic Speed Controllers (ESCs)
- Four **ESCs** are connected to the ESP32.
- Each ESC is responsible for controlling one **Brushless DC (BLDC) motor**, providing precise speed control.

### BLDC Motors
- The quadcopter is equipped with four **BLDC motors**.
- These motors provide the necessary thrust and maneuverability for the quadcopter.

### MPU6050 - Motion Processing Unit
- Connected to the ESP32, the **MPU6050** sensor module provides gyroscopic and accelerometer data.
- This data is crucial for stabilizing the quadcopter and for pitch, roll, and yaw adjustments.

### GPS Neo8m Module
- The **GPS Neo8m module** offers location tracking capabilities.
- It provides valuable data for navigation and autonomous flight features.

### Power Distribution Board (PDB) and Battery
- All components are connected to a **Power Distribution Board (PDB)**.
- The quadcopter is powered by a **LiPo 4s battery**, ensuring adequate power supply for extended flight times.

![Drone layout](img/drone.jpg)

## Cascading PID Control for Movement

### Overview of Cascading PID
- A **Cascading PID** system involves multiple layers of PID controllers, each responsible for different aspects of control.
- This hierarchical structure enables finer tuning and responsive adjustments.

### Pitch-Roll-Yaw Control
#### Pitch control
- **Objective**: To manage the forward and backward tilt.
- **Outer Loop PID**: Focuses on desired pitch angle, setting a target for the inner loop.
- **Inner Loop PID**: Directly controls motor speeds to achieve the desired pitch angle.
- **Benefits**: Allows for precise control of forward and backward movements, essential for smooth flight.
#### Roll Control
- **Objective**: To manage the side-to-side tilt.
- **Outer Loop PID**: Sets the target roll angle based on desired lateral movement.
- **Inner Loop PID**: Adjusts motor speeds to match the target roll angle.
- **Benefits**: Enables precise control over left and right movements, critical for maintaining balance and direction.

#### Yaw Control
- **Objective**: To control the rotation around the vertical axis.
- **Outer Loop PID**: Determines the target yaw angle for directional orientation.
- **Inner Loop PID**: Modifies the rotational speeds of the motors to achieve the target yaw angle.
- **Benefits**: Essential for accurate directional control, allowing the quadcopter to face and move in the desired direction.