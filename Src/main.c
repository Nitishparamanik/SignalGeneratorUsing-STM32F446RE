/**
 * @file main.c
 * @brief Main application file for generating waveforms using STM32F446RE.
 *
 * This file initializes the GPIO, DAC, and EXTI peripherals. It contains the main loop
 * which continuously generates different waveforms based on the current mode. The mode
 * and frequency of the waveforms can be changed using external push buttons.
 *
 * - PA4: DAC output
 * - PC13: Change waveform mode (Sine, Square, Triangle)
 * - PA7: Change waveform frequency
 * - PA5: LED indicator for waveform mode change
 * - PA6: LED indicator for frequency change
 */
#include "stm32f446xx.h"
#include "gpio.h"
#include "waveforms.h"
#include "sysTick.h"

// Define SystemCoreClock for this example
#define SystemCoreClock 180000000U  // 180 MHz

extern uint8_t waveform_mode;
extern uint32_t frequency;

int main() {
    // Initialize GPIO, DAC, and EXTI
    GPIO_Init();

    // Initialize SysTick timer
    SysTick_Init(SystemCoreClock / 1000); // 1 ms tick

    // Main loop
    while (1) {
        switch (waveform_mode) {
            case 0: SineWave(); break;
            case 1: SquareWave(); break;
            case 2: TriangleWave(); break;
        }
    }
}
