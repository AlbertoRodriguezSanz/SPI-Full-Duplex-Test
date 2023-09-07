# SPI-Master-Full-Duplex-Test

PIC firmware for performing a communication test between two PIC18F26K83 microcontrollers through the SPI communication protocol. The goal for this test is to exchange a total of 4 bytes uninterrupted, replicating the communication with the AksIM2 absolute encoder. If the received message matches an expected value the LED will be turned on., where the goal for the first is for the master to simply exchange one message with the slave, while the goal of the second. There are three implementations 

## Setup
A breadboard with two PIC18F26K83 microcontrollers connected through two MCP2561 CAN transceivers is used as a testbench. 

![broadboard_can_bus_top_viewjpg](https://github.com/AlbertoRodriguezSanz/CAN-Bus-Test/assets/95371514/c0f4a20e-199d-4b0a-b0b2-8a69f7578277) 

For this test the PICkit4 in-circuit debugger/programmer will be used to load the firmware into the microcontroller. This needs to be connected to the microcontroller with the following pins.
- MCLR
- PGD
- PGC
- VDD
- VSS
  
![pickit4 connections](https://github.com/AlbertoRodriguezSanz/CAN-Bus-Test/assets/95371514/aca34265-d625-4ffe-b99b-b4cd80b32269)

Unlike what is specified on the PICkit4 manual, microcontrollers need to add a second series resistor to the MCLR pin. Recommended values for the two resistrors are 10kΩ (R1) and 470Ω max.(R2).

![mclr connection](https://github.com/AlbertoRodriguezSanz/CAN-Bus-Test/assets/95371514/b95aa3bf-8a20-4b94-be2d-364be542fe47)

The microcontrollers are connected through two MCP2561 CAN transceivers. The two "programming" connectors represent the PICKIT4 pins shown previously.

![protoboard_schematic](https://github.com/AlbertoRodriguezSanz/CAN-Bus-Test/assets/95371514/cc8b1035-44ea-4e5a-bbfc-5b08e4b7b556)



## ECAN module configuration

The following parameters are configured with the Microchip Code Configurator plugin (MCC):
- Clock Settings
  - Clock Source: Use system clock as CAN system clock
  - Clock Frequency: 16MHz
- Bit Rate Settings
  - CAN bus speed: 1Mbps
  - Time Quanta: 8
  - Sync Jumpt Width: 1xTQ
  - Sample Point: 75%
  - Phase Segment 1: 4xTQ
  - Phase Segment 2: 2xTQ
  - Propagation Segment: 1xTQ
- Transmit-Receive Settings
  - Operation Mode: Mode 0 (Legacy)
  
## Requirements

Install MPLAB X IDE tool for Windows, Linux or MAC from the following link ([download link](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide#tabs)).

## How to download the firmware to the PIC

Once MPLAB is opened, load the project through *File > Open Project* and then select the file `CAN_bus_x.mc3`, where X denotates the firmware for each of the microcontrollers.
This will open the work environment, where `main.c` is the code file that will be compiled into the PIC. The project properties are accessed through *Production > Set Project Configuration > Customize...*, where the PICkit4 needs to be selected in the *Connected Hardware Tool* menu.
![Screenshot from 2023-09-01 14-19-52](https://github.com/AlbertoRodriguezSanz/CAN-Bus-Test/assets/95371514/248a38f8-ebf5-4f62-97c1-47c6fd496216)

Modify the following options from the default parameters for the PICkit4 programmer from the Option categories dropdown menu.
-Power
  - Power target circuit from PICkit4.
  - Voltage Level: 5V.
- PICkit4 Tool Options
  - Program Speed: Low (Otherwise an error will pop up when trying to load the firmware).

Then, follow the next steps:
* Compile: `Production> Build Main Project`
* Program: `Production> Make and Program Device Main Project`
