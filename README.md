# STM32F446RE Signal Generator

## Project Overview
This project implements a signal generator system using the STM32F446RE microcontroller. It generates sine, square, and triangle waveforms with user control over waveform type and frequency via push buttons. LEDs provide feedback on the selected waveform and frequency changes.

## Features
- **Waveform Generation**: Supports sine, square, and triangle waveforms.
- **User Input**: Change waveform type using the on-board push button (PC13).
- **Frequency Control**: Adjust the waveform frequency using an external push button (PA7).
- **LED Indicators**: Two LEDs (PA5 and PA6) indicate waveform and frequency changes.

## Components
- **STM32F446RE Nucleo Board**
- **DAC (PA4)**: Converts digital values to analog signals to generate waveforms.
- **GPIO Pins**: PA5 and PA6 for LED indicators, PC13 and PA7 for push buttons.
- **SysTick Timer**: Controls the timing for waveform generation.

## Connection Details
| Peripheral        | Port & Pin | Mode   | Description                             |
|-------------------|------------|--------|-----------------------------------------|
| LED1              | PA5        | Output | Indicates changes in waveform mode      |
| LED2              | PA6        | Output | Indicates changes in waveform frequency |
| On-board Button   | PC13       | Input  | Changes waveform type                   |
| External Button   | PA7        | Input  | Changes frequency                       |
| DAC               | PA4        | Analog | Outputs the waveform signal             |

## Algorithm
1. **Initialization**: Set up GPIO, DAC, and EXTI for input buttons.
2. **Interrupt Handlers**: Handle waveform change and frequency adjustment interrupts.
3. **Waveform Generation**: Generate sine, square, or triangle waves using lookup tables and update the DAC output.
4. **Main Loop**: Continuously monitor user input and adjust the waveform or frequency accordingly.

## Future Scope
- LCD Display for better UI.
- Arbitrary waveform generation.
- Data logging for analysis.

## Output
- Wave shape changes on pressing the on-board button (PC13).
- Frequency changes on pressing the external button (PA7).

## Conclusion
This project demonstrates the STM32F446RE microcontroller's capability to handle real-time waveform generation and user input. It is a valuable tool for signal processing, testing, and teaching.
