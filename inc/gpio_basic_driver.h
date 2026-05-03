#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#define HIGH 1
#define LOW 0

/* ===================== REGISTER DEFINITIONS ===================== */

#define GPIO_BASE_ADDR 0x3FF44000	//Base Address of GPIO Peripheral
#define GPIO_ENABLE_REG     (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x20))	//GPIO Enable Register. Controls direction of GPIO pins (1 = output, 0 = input)
#define GPIO_OUT_REG        (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x04))	//GPIO Output Register. Holds current output values of GPIO pins
#define GPIO_IN_REG         (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x3C))	//GPIO Input Register. Used to read input values from GPIO pins
#define GPIO_OUT_W1TS_REG   (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x08))	//GPIO Output Set Register. Writing '1' to a bit sets the corresponding GPIO pin HIGH
#define GPIO_OUT_W1TC_REG   (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x0C))	//GPIO Output Clear Register. Writing '1' to a bit sets the corresponding GPIO pin LOW

/* ===================== GPIO MODES ===================== */
typedef enum {
    GPIO_INPUT = 0,
    GPIO_OUTPUT
} gpio_mode_t;


/* ===================== FUNCTION PROTOTYPE ===================== */

/**
 * @brief Initialize a GPIO pin as input or output
 *
 * This function configures the direction of a GPIO pin.
 * 
 *
 * @param pin GPIO pin number (0–39)
 * @param mode GPIO mode configuration:
 *             GPIO_INPUT  
 *             GPIO_OUTPUT
 *             
 *            
 *
 * @note Pins above 39 are invalid and ignored
 *    
 */
void gpio_init(uint8_t pin, gpio_mode_t mode);

/**
 * @brief Write a value to a GPIO pin
 *
 * This function sets or clears the specified GPIO pin.
 *
 * Pull resistors help prevent floating input states.
 *
 * @param pin GPIO pin number (0–39)
 * @param value HIGH = 1 and LOW = 0
 *
 */
void gpio_write(uint8_t pin, uint8_t value);

/**
 * @brief Read the current state of a GPIO pin
 *
 *
 * @param pin GPIO pin number (0-39)
 * @note Returns 0 for invalid pins
 * 
 */
uint8_t gpio_read(uint8_t pin);


/**
 * @brief Toggle the current state of a GPIO pin
 *
 * @param pin GPIO pin number (0–39)
 */
void gpio_toggle(uint8_t pin);

#endif
