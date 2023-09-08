## SPI module configuration

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
