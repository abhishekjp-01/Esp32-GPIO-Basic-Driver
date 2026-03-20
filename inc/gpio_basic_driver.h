#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#define HIGH 1
#define LOW 0

/* ===================== GPIO MODES ===================== */
typedef enum {
    GPIO_INPUT = 0,
    GPIO_OUTPUT
} gpio_mode_t;

/* ===================== FUNCTION PROTOTYPE ===================== */
void gpio_init(uint8_t pin, gpio_mode_t mode);
void gpio_write(uint8_t pin, uint8_t value);
uint8_t gpio_read(uint8_t pin);
void gpio_toggle(uint8_t pin);

#endif
