# Autonomous Object-Following Robot

## Description

This repository contains the code and documentation for an autonomous object-following robot project. The robot is powered by a PIC18 microcontroller and uses infrared (IR) sensors to detect objects or people within a certain distance range (40cm to 150cm) and follows them at a similar speed. The robot can be controlled using a remote control, and it is equipped with features such as battery monitoring and low voltage warning.

## Table of Contents

1. [Introduction](#introduction)
2. [Components](#components)
3. [Setup](#setup)
4. [Usage](#usage)
5. [Calculations](#calculations)
6. [Simulations](#simulations)
7. [Conclusion](#conclusion)
8. [Improvements](#improvements)

## Introduction

The goal of this project was to design and build an autonomous robot capable of following objects or people within a specified distance range. The robot utilizes infrared sensors to detect the presence of objects and adjust its speed accordingly to keep up with them. Additionally, it can be controlled using a remote control for manual operation.

## Components

The main components used in this project are as follows:

- PIC18 Microcontroller
- Infrared (IR) Sensors
- Motor Driver
- Remote Control
- Battery Voltage Monitor
- LEDs for Battery Level Display

## Setup

To set up the robot, follow these steps:

1. Assemble the robot chassis and attach the motors.
2. Connect the IR sensors and motor driver to the PIC18 microcontroller.
3. Connect the battery voltage monitor and LEDs for battery level display.
4. Set up the remote control to communicate with the robot.

## Usage

The robot has two modes of operation:

1. Autonomous Mode: The robot uses its IR sensors to detect objects and follows them automatically within the specified distance range.

2. Manual Mode: The robot can be controlled using a remote control. The central button on the remote control starts or stops the robot, depending on its current state.

## Calculations

The project involves various calculations, including:

- Period of the ADC (Analog-to-Digital Converter)
- PWM Generation for Motors
- Timer0 for Base Time Calculation

## Simulations

The robot's functionalities have been simulated using Proteus software. Simulations include:

- Timer0 period verification
- PWM signal generation for motors
- Battery voltage monitoring and LED display
- IR sensor readings and object detection

## Conclusion

This project successfully achieved its objective of building an autonomous object-following robot using the PIC18 microcontroller and IR sensors. The robot is capable of detecting and following objects or people within the specified distance range. The battery voltage monitoring and low voltage warning features enhance the robot's usability and efficiency.

## Improvements

Possible improvements for the future:

- Implementing debounce filters for the remote control to avoid signal fluctuations.
- Adding a buzzer for low voltage alerts to ensure prompt user attention.
- Upgrading to a higher capacity lithium polymer battery for extended operation.
- Fine-tuning the PWM frequency to match the 1 ms base time requirement specified in the original design.

Feel free to contribute to the project and make it even better!
