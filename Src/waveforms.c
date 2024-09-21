/**
 * @file waveforms.c
 * @brief Waveform generation functions.
 *
 * This file contains functions to generate different waveforms using the DAC.
 * The available waveforms are Sine, Square, and Triangle. These functions use
 * a global delay variable to control the frequency of the waveforms.
 *
 * - SineWave: Generates a sine waveform.
 * - SquareWave: Generates a square waveform.
 * - TriangleWave: Generates a triangle waveform.
 */
#include "stm32f446xx.h"
#include "waveforms.h"
#include <math.h>
#include "sysTick.h"

// Define global variables for waveform generation
float val = 0.0;
uint32_t step = 0;
uint32_t data_value = 0;

extern uint32_t frequency;

void SineWave() {
    data_value = (uint32_t)(sin(val * M_PI / 180.0) * (4095.0 / 3.3));
    DAC->DHR12R1 = data_value;
    DAC->SWTRIGR |= (1 << 0);

    val += 0.1;
    if (val >= 360.0) {
        val = 0.0;
    }

    Delay(frequency);
}

void SquareWave() {
    data_value = (step < 2048) ? 4095 : 0;
    DAC->DHR12R1 = data_value;
    DAC->SWTRIGR |= (1 << 0);

    step++;
    if (step >= 4096) {
        step = 0;
    }

    Delay(frequency);
}

void TriangleWave() {
    data_value = (step < 2048) ? (step * (4095 / 2048)) : ((4095 - step) * (4095 / 2048));
    DAC->DHR12R1 = data_value;
    DAC->SWTRIGR |= (1 << 0);

    step++;
    if (step >= 4096) {
        step = 0;
    }

    Delay(frequency);
}
