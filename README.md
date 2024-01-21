 Quadcopter Project: Advanced Movement Control

## Introduction

This document details the advanced movement control system implemented in the Quadcopter Project, focusing on the use of a cascading PID (Proportional-Integral-Derivative) control system to manage the pitch, roll, and yaw movements. The integration of these technologies ensures precise and responsive maneuvering of the quadcopter.

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