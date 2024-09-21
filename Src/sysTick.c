/**
 * @file sysTick.c
 * @brief SysTick timer initialization and delay functions.
 *
 * This file contains functions to initialize the SysTick timer and provide a
 * delay function. The delay function uses the SysTick timer to create precise
 * delays based on the system core clock.
 */
#include "stm32f446xx.h"
#include "pll.h"
#include "sysTick.h"
volatile uint32_t ms_counter = 0;
volatile uint32_t millis = 0;

void SysTick_Init(){
    SysTick->VAL = 0;
    SysTick->LOAD = (HCLK_FREQ / 1000)- 1;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk |
                    SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(){
    if (ms_counter) ms_counter--;
    millis++;
}

void delay_ms(uint32_t ms){
    ms_counter = ms;
    while (ms_counter);
}

uint32_t getMillis(){
    return millis;
}
void Delay(uint32_t delay) {
    SysTick->LOAD = delay - 1;   // Set reload register
    SysTick->VAL = 0;            // Reset the SysTick counter value
    SysTick->CTRL |= 1;          // Start SysTick

    while (!(SysTick->CTRL & (1 << 16))); // Wait for the COUNTFLAG

    SysTick->CTRL &= ~1;         // Stop SysTick
}
