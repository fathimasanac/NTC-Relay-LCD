# NTC Thermistor with Relay and LCD

This project uses an **ATmega2560**, a 16x2 LCD, an **NTC thermistor**, and a relay module to control a device based on temperature.

## Circuit Diagram / Simulation
You can view and run the circuit online using Wokwi:

[Open Simulation in Wokwi](https://wokwi.com/projects/442804265175499777)

## Features
- Reads temperature from NTC thermistor
- Displays temperature on LCD
- Turns relay ON if temp ≥ 38°C
- Turns relay OFF if temp < 38°C

## Arduino Code Overview
- Reads analog value from NTC thermistor  
- Converts it to temperature using **Steinhart-Hart equation**  
- Displays temperature on **LCD line 1**  
- Displays relay status (ON/OFF) on **LCD line 2**  
- Controls relay based on temperature thresholds  
