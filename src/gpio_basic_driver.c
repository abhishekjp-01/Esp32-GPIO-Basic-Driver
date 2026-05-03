/*
 * @file gpio_basic_driver.c
 * 
 * This file contains the implementation of basic GPIO functionalities
 * using direct register access based on ESP32 Technical Reference Manual.
 *
 * Features:
 * 	GPIO initialization (input/output)
 * 	GPIO write (set/clear)
 * 	GPIO read
 * 	GPIO toggle
 */


#include "gpio_basic_driver.h"


/* ===================== FUNCTION IMPLEMENTATION ===================== */
void gpio_init(uint8_t pin, gpio_mode_t mode)
{
    if (pin > 39) return;

    if (mode == GPIO_OUTPUT)
        GPIO_ENABLE_REG |= (1 << pin);
    else
        GPIO_ENABLE_REG &= ~(1 << pin);
}


void gpio_write(uint8_t pin, uint8_t value)
{
    if (pin > 39) return;

    if (value)
        GPIO_OUT_W1TS_REG = (1 << pin);
    else
        GPIO_OUT_W1TC_REG = (1 << pin);
}


uint8_t gpio_read(uint8_t pin)
{
    if (pin > 39) return 0;
    return (GPIO_IN_REG >> pin) & 0x01;
}


void gpio_toggle(uint8_t pin)
{
    if (pin > 39) return;

    if (GPIO_OUT_REG & (1 << pin))
        GPIO_OUT_W1TC_REG = (1 << pin);
    else
        GPIO_OUT_W1TS_REG = (1 << pin);
}
