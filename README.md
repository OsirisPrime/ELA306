# Autonomous Tire Pressure Adaptation for Polestar 3

## Overview

This project investigates an **autonomous tire-pressure adaptation system** for the Polestar 3. The objective is to dynamically adjust tire pressure according to driving conditions such as vehicle speed and road friction.

The project was developed as a **MATLAB/Simulink simulation** of a closed-loop tire-pressure control system. The model combines tire-pressure sensing, state-based reference-pressure selection, PID control, a compressor, and an exhaust valve.

The purpose of the system is to improve:

* Vehicle stability
* Tire-road grip
* Energy efficiency
* Tire wear
* Adaptability to changing driving conditions

The simulation focuses on **one wheel** as a simplified representation of the complete system.

---

## Project Objective

The Polestar 3 is a relatively heavy electric vehicle with high available torque. These characteristics place additional demands on the tires, particularly during acceleration and changing road conditions.

A fixed tire pressure does not provide optimal performance under all conditions. Therefore, the proposed system dynamically changes the target tire pressure depending on the current driving situation.

The simulated system uses:

* A tire-pressure sensor
* An electric compressor
* An electrically controlled exhaust valve
* A PID controller
* StateFlow-based reference-pressure selection
* Feedback from the tire-pressure measurement

The overall system is designed as a **closed-loop control system**.

---

## System Architecture

The simulated system consists of the following main components:

```text
                 Driving Conditions
                        │
                        ▼
                 ┌──────────────┐
                 │   StateFlow  │
                 │ Target       │
                 │ Pressure     │
                 └──────┬───────┘
                        │
                        ▼
                  Target Pressure
                        │
                        ▼
                 ┌──────────────┐
                 │ PID          │
                 │ Controller   │
                 └──────┬───────┘
                        │
                        ▼
                   Compressor
                        │
                        ▼
                  ┌───────────┐
                  │   Tire    │
                  │ 0.09 m³   │
                  └─────┬─────┘
                        │
                        ▼
                  TPMS Sensor
                        │
                        ▼
                 Measured Pressure
                        │
                        └──────────────► Feedback
```

When the pressure becomes too high, a separate control path activates the exhaust valve to release air.

---

## Target Pressure Strategy

The reference pressure is selected using StateFlow.

Three main operating conditions are simulated:

| Driving condition | Target pressure |
| ----------------- | --------------: |
| Standard          |         2.7 bar |
| High speed        |         2.9 bar |
| High friction     |         2.5 bar |

The standard reference value is **2.7 bar**.

At higher speeds, the target pressure is increased to **2.9 bar** to reduce tire deformation and rolling resistance.

For high-friction conditions, the target pressure is reduced to **2.5 bar**, allowing greater tire deformation and contact with the road surface.

The StateFlow model can be extended with additional operating states and reference pressures.

---

## Control System

### PID Controller

A PID controller is used to regulate the tire pressure.

The controller compares the measured tire pressure with the desired reference pressure:

```text
Error = Target Pressure - Measured Pressure
```

The PID controller then generates the control signal for the compressor.

The controller contains:

* Proportional term
* Integral term
* Derivative term

The use of PID control provides a relatively simple and robust method for continuously regulating the pressure.

### Pressure Release

A separate exhaust-control system handles overpressure.

When the pressure error becomes negative, indicating that the actual pressure is above the target pressure, the exhaust valve receives a signal to open.

```text
Target Pressure
       │
       ▼
Measured Pressure
       │
       ▼
   Error Logic
       │
       ├── Positive error ──► Compressor
       │
       └── Negative error ──► Exhaust Valve
```

---

## TPMS Sensor Model

The TPMS sensor is modelled to reproduce the behaviour of the selected pressure sensor.

The simulated sensor:

1. Limits the pressure signal to **0–8 bar**
2. Quantizes the signal to represent the sensor's digital output
3. Holds the measurement for **1 second**
4. Converts the pressure to bar
5. Applies low-pass filtering
6. Provides the filtered pressure to the control system

The simulated sampling frequency is therefore **1 Hz**.

---

## Tire Model

The tire is represented as a closed air chamber with a volume of approximately:

```text
V = 0.09 m³
```

The pressure dynamics are based on the ideal gas law:

```text
pV = nRT
```

where:

* `p` = tire pressure
* `V` = tire volume
* `n` = amount of substance
* `R` = gas constant
* `T` = temperature

For the simulation, the temperature is assumed to remain constant.

The compressor changes the amount of air inside the tire, which changes the tire pressure.

---

## Simulink Models

The repository contains several MATLAB/Simulink models used during development and simulation.

### Main Models

#### `CompletePhysicalTireSystem.slx`

Complete simulation of the tire-pressure adaptation system.

#### `CompletePhysicalTireSystem_new.slx`

Alternative/newer version of the complete physical tire-system model.

#### `TirePressureSignalLogic.slx`

Model containing the tire-pressure signal processing and control logic.

#### `system.slx`

System-level simulation model.

### MATLAB Files

#### `Variables.mlx`

MATLAB Live Script containing model parameters and variables.

#### `Variables_new.mlx`

Updated version of the parameter/variable definitions.

---

## Simulation Modes

The simulated system can operate using either a constant or changing target-pressure condition.

### Constant Mode

The desired pressure remains constant during the simulation.

Example:

```text
2.7 bar ─────────────────────────────
```

This mode can be used to investigate the basic stability and response of the pressure-control system.

### Variable Mode

The target pressure changes during the simulation according to the selected driving condition.

Example:

```text
2.7 bar ─────► 2.9 bar ─────► 2.5 bar
 standard       high speed      high friction
```

This mode demonstrates the adaptive behaviour of the system.

---

## Proposed Hardware

The project also investigated physical components suitable for implementing the system.

The proposed components include:

* **ARB CKMTA12** 12 V compressor
* **WHP TPMS** pressure sensor
* Festo check valve
* 12 V two-way solenoid valve
* **Caleffi 527 EST** overpressure valve

The overpressure valve provides an additional safety mechanism. It is intended to prevent the tire from reaching dangerously high pressures in the event of a compressor-control failure.

---

## Product Requirements

The proposed system was developed around several requirements:

| Requirement             | Target           |
| ----------------------- | ---------------- |
| Pressure accuracy       | 0.1 bar          |
| Sensor update frequency | ≥ 1 Hz           |
| Operating temperature   | −40 °C to +40 °C |
| Power supply            | 12 V             |
| Pressure adjustment     | Automatic        |
| Control                 | Closed-loop      |

The system is intended to provide a short feedback loop between pressure measurement and pressure adjustment.

---

## Simulation Results

The simulations demonstrated that the proposed system can continuously adjust tire pressure.

For the simulated tire:

* Increasing pressure from **1.0 bar to 2.7 bar** takes approximately **90 seconds**.
* Increasing pressure by approximately **0.2 bar** takes around **30 seconds**.
* Reducing pressure by approximately **0.2 bar** takes around **80 seconds**.
* Maximum simulated volumetric flow is approximately **0.0013 m³/s**.

The simulations also estimated energy consumption for pressure changes:

| Pressure sequence   | Simulation time |   Energy |
| ------------------- | --------------: | -------: |
| 1.0 → 2.7 → 2.9 bar |          ~150 s | ~59.3 kJ |
| 1.0 → 2.7 → 2.5 bar |          ~200 s | ~59.7 kJ |

The model demonstrated stable pressure adjustment without significant oscillation under the simulated conditions.

---

## Limitations

The simulation is a simplified representation of a real vehicle system.

The following factors are not fully represented:

* Tire rotation
* Dynamic forces while driving
* Actual road friction measurements
* A physical friction sensor
* Air leakage
* Non-linear compressor behaviour
* Compressor efficiency and losses
* Temperature variations
* Latency between sensor measurements and actuator response
* Mechanical forces acting on the components

The tire is also represented as a constant-volume air chamber.

Because of these simplifications, the current model should be considered a **first-stage simulation**, rather than a complete representation of a production-ready tire-pressure system.

---

## Future Development

Further development could extend the model to include:

* Four independent tires
* Real-time friction sensing
* Vehicle-speed input
* Tire rotation
* Temperature-dependent pressure changes
* Compressor efficiency and losses
* Air leakage
* Sensor and actuator latency
* More StateFlow operating conditions
* Dynamic driving simulations
* Physical prototype testing

A four-wheel implementation could use the simulated single-wheel model as the basis for each individual tire.

---

## Requirements

To work with the simulation, a MATLAB installation with **Simulink** is required.

The project uses MATLAB Live Scripts (`.mlx`) and Simulink models (`.slx`).

Recommended workflow:

1. Open MATLAB.
2. Navigate to the project directory.
3. Open the relevant `.mlx` file.
4. Run the variable/parameter definitions.
5. Open the desired `.slx` model.
6. Run the simulation.
7. Inspect the pressure response and controller behaviour.

---

## Repository Structure

The main project files are organized around the MATLAB/Simulink models:

```text
Project/
│
├── CompletePhysicalTireSystem.slx
├── CompletePhysicalTireSystem_new.slx
├── TirePressureSignalLogic.slx
├── system.slx
│
├── Variables.mlx
├── Variables_new.mlx
│
└── Project Report.pdf
```

The exact model to use depends on which version of the simulation is being investigated.

---

## Project Report

The accompanying **Project Report.pdf** contains the detailed background, system requirements, component selection, modelling methodology, control strategy, simulation results, limitations, and conclusions behind the project.

The repository README provides a concise overview, while the report contains the detailed engineering analysis.

---

## Conclusion

This project demonstrates a MATLAB/Simulink-based concept for **autonomous tire-pressure adaptation in a Polestar 3**.

A closed-loop system consisting of a TPMS sensor, StateFlow reference selection, PID controller, compressor, and exhaust valve was developed and simulated.

The results indicate that autonomous pressure adjustment is feasible for a stationary tire using a 12 V-based system. However, additional modelling and testing are required before the concept can be transferred to dynamic driving conditions.

The current model therefore serves as a foundation for further development of an autonomous tire-pressure monitoring and adaptation system.
