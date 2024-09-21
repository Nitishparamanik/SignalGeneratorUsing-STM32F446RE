/*
 * gpio.c
 *
 *  Created on: Jul 30, 2024
 *      Author: Nitish Paramanik
 */

/**
 * @file gpio.c
 * @brief GPIO and EXTI initialization and interrupt handling.
 *
 * This file initializes the GPIO pins for DAC output, push buttons, and LEDs. It also
 * sets up the EXTI (External Interrupt) for the push buttons to handle waveform mode
 * and frequency changes. The interrupt handlers are implemented to toggle the LEDs
 * and update the mode or frequency accordingly.
 *
 * - GPIOA: PA4 (DAC output), PA5 (LED for mode change), PA6 (LED for frequency change), PA7 (Frequency change button)
 * - GPIOC: PC13 (Waveform mode change button)
 */
#include "stm32f446xx.h"
#include "gpio.h"

// External variables to control the waveform mode and frequency
uint8_t waveform_mode = 0;
uint32_t frequency = 50000; // Base delay for waveform generation

void GPIO_Init() {
    // Enable GPIOA and GPIOC clock
    RCC->AHB1ENR |= (1 << 0) | (1 << 2);

    // Set PA4 to Analog mode
    GPIOA->MODER &= ~(3 << 8);  // Reset PA4
    GPIOA->MODER |= (3 << 8);   // Set PA4 to Analog mode

    // Set PA5 and PA6 to output mode (LED indicators)
    GPIOA->MODER |= (1 << (5 * 2)) | (1 << (6 * 2));

    // Set PA7 to input mode (Frequency change button)
    GPIOA->MODER &= ~(3 << (7 * 2));
    GPIOA->PUPDR &= ~(3 << (7 * 2));  // Reset pull-up/pull-down
    GPIOA->PUPDR |= (1 << (7 * 2));   // Set pull-up for PA7

    // Set PC13 to input mode (Waveform change button)
    GPIOC->MODER &= ~(3 << (13 * 2));
    GPIOC->PUPDR &= ~(3 << (13 * 2));  // Reset pull-up/pull-down
    GPIOC->PUPDR |= (1 << (13 * 2));   // Set pull-up for PC13

    // Enable DAC clock
    RCC->APB1ENR |= (1 << 29);

    // Configure DAC Channel 1
    DAC->CR |= (1 << 0);  // Enable DAC
    DAC->CR &= ~(1 << 1); // Disable DAC buffer
    DAC->CR |= (7 << 3);  // Set Trigger to Software trigger
    DAC->DHR12R1 = 0;     // Reset DAC value

    // Initialize EXTI for PC13 and PA7
    EXTI_Init();
}

void EXTI_Init() {
    // Enable SYSCFG clock
    RCC->APB2ENR |= (1 << 14);

    // Configure EXTI13 for PC13 (Waveform change button)
    SYSCFG->EXTICR[3] &= ~(0xF << (13 % 4 * 4)); // Reset EXTI13 configuration
    SYSCFG->EXTICR[3] |= (2 << (13 % 4 * 4));    // Set EXTI13 to use PC13

    // Configure EXTI7 for PA7 (Frequency change button)
    SYSCFG->EXTICR[1] &= ~(0xF << (7 % 4 * 4)); // Reset EXTI7 configuration
    SYSCFG->EXTICR[1] |= (0 << (7 % 4 * 4));    // Set EXTI7 to use PA7

    // Configure EXTI lines
    EXTI->IMR |= (1 << 13) | (1 << 7); // Unmask EXTI13 and EXTI7
    EXTI->FTSR |= (1 << 13) | (1 << 7); // Falling edge trigger

    // Enable EXTI line interrupts
    NVIC_EnableIRQ(EXTI15_10_IRQn); // For PC13
    NVIC_EnableIRQ(EXTI9_5_IRQn);   // For PA7
}

void EXTI15_10_IRQHandler(void) {
    if (EXTI->PR & (1 << 13)) {  // Check if EXTI13 triggered
        EXTI->PR |= (1 << 13);   // Clear pending bit

        // Change waveform mode
        waveform_mode++;
        if (waveform_mode > 2) {
            waveform_mode = 0;
        }

        // Update LED indicators
        GPIOA->ODR ^= (1 << 5); // Toggle PA5 to indicate waveform change
    }
}

void EXTI9_5_IRQHandler(void) {
    if (EXTI->PR & (1 << 7)) {  // Check if EXTI7 triggered
        EXTI->PR |= (1 << 7);    // Clear pending bit

        // Change frequency (adjust the base delay for waveform generation)
        frequency += 10000; // Increase frequency
        if (frequency > 200000) { // Reset frequency after reaching maximum
            frequency = 50000;
        }

        // Update LED indicators
        GPIOA->ODR ^= (1 << 6); // Toggle PA6 to indicate frequency change
    }
}
