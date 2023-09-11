### SPI Slave device

This device's firmware is programmed without the abstraction given by the use of MCC, in a single file, which contains all of the required functions for initialization and operation. 

## Device configuration

- Configuration bits (CONFIG1-5H/L registers)
  - Oscillator source at power-up: High frequency internall oscillator with no clock division applied
  - Master Clear and Low Voltage Programming: MCLR and LVP are enabled, making the MCLR pin work for as a master clear for programming.
  - Brown-out Reset: Disabled, device will not reset when voltage drops under a certain threshold.
  - Watchdog Timer: Disabled, the Windowed Watchdog Timer will not be enabled for this test, to check for timing inaccuracies while executing instructions.
- Clock Manager (OSCCON1 and OSCFRQ registers)
  -   Clock Frequency: 16MHz, proceeding from a 64MHz base High-Frequency Oscillator Clock
- Pin Manager:
  -  Slave Select -> RA5 (input)
  -  SPI clock -> RC3 (input)
  -  SPI Data Out (SDO) -> RC5 (output)
  -  SPI Data In (SDI) -> RC4 (input)

## SPI module configuration

- SPI Mode 0
  - Bit Count Mode (BMODE): 0
  - Bus: Slave
  - MSB transmitted first
  - Sample Data Inout: Middle
  - Clock Transition: Active to Idle
  - Idle State of Clock: Low Level
  - Slave Select Active: Low Level
  - SDI Active: High Level
  - SDO Active: High Level
- Slave Transfer Settings
  - SDO transfers: according to the level of Slave Select
  - Transmit: Enabled
  - Receive: Enabled
- Clock Settings
  - Clock Source: High Frequency Internall Oscillator
  - Baud Clock: 4MHz
- Implemented Functions
  - ExchangeByte  
