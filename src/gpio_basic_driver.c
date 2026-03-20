/*
 * @file gpio.c
 * 
 * This file contains the implementation of basic GPIO functionalities
 * using direct register access based on ESP32 Technical Reference Manual.
 *
 * Features:
 * 	GPIO initialization (input/output)
 * 	GPIO write (set/clear)
 * 	GPIO read
 * 	GPIO toggle
 *
 */


#include "gpio.h"

/* ===================== MACROS & REGISTER DEFINITIONS ===================== */

#define GPIO_BASE_ADDR 0x3FF44000	//Base Address of GPIO Peripheral
#define GPIO_ENABLE_REG     (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x20))	//GPIO Enable Register. Controls direction of GPIO pins (1 = output, 0 = input)
#define GPIO_OUT_REG        (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x04))	//GPIO Output Register. Holds current output values of GPIO pins
#define GPIO_IN_REG         (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x3C))	//GPIO Input Register. Used to read input values from GPIO pins
#define GPIO_OUT_W1TS_REG   (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x08))	//GPIO Output Set Register. Writing '1' to a bit sets the corresponding GPIO pin HIGH
#define GPIO_OUT_W1TC_REG   (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x0C))	//GPIO Output Clear Register. Writing '1' to a bit sets the corresponding GPIO pin LOW

/* ===================== FUNCTION IMPLEMENTATION ===================== */
/**
 * @brief Initialize a GPIO pin as input or output
 *
 * This function configures the direction of a GPIO pin.
 *
 * @param pin  GPIO pin number (0–39)
 * @param mode GPIO_INPUT or GPIO_OUTPUT
 *
 * @note Pins above 39 are invalid and ignored
 */
void gpio_init(uint8_t pin, gpio_mode_t mode)
{
    if (pin > 39) return;

    if (mode == GPIO_OUTPUT)
        GPIO_ENABLE_REG |= (1 << pin);
    else
        GPIO_ENABLE_REG &= ~(1 << pin);
}

/*---------------------------------------------------------------------*/

/**
 * @brief Write a value to a GPIO pin
 *		  Sets or clears the specified GPIO pin.
 *
 * @param pin   GPIO pin number (0–39)
 * @param value 1 = HIGH, 0 = LOW
 */
void gpio_write(uint8_t pin, uint8_t value)
{
    if (pin > 39) return;

    if (value)
        GPIO_OUT_W1TS_REG = (1 << pin);
    else
        GPIO_OUT_W1TC_REG = (1 << pin);
}

/*---------------------------------------------------------------------*/

/**
 * @brief Read the current state of a GPIO pin
 *
 * @param pin GPIO pin number (0–39)
 * 
 * @note Returns 0 for invalid pins
 */
uint8_t gpio_read(uint8_t pin)
{
    if (pin > 39) return 0;
    return (GPIO_IN_REG >> pin) & 0x01;
}

/*---------------------------------------------------------------------*/

/**
 * @brief Toggle the current state of a GPIO pin

 * @param pin GPIO pin number (0–39)
 */
void gpio_toggle(uint8_t pin)
{
    if (pin > 39) return;

    if (GPIO_OUT_REG & (1 << pin))
        GPIO_OUT_W1TC_REG = (1 << pin);
    else
        GPIO_OUT_W1TS_REG = (1 << pin);
}

