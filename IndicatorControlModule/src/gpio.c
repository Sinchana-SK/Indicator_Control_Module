#include "gpio.h"

void GPIO_SetOutput(volatile uint8_t *ddr, uint8_t pin) {
    *ddr |= (1 << pin);
}

void GPIO_SetInput(volatile uint8_t *ddr, uint8_t pin) {
    *ddr &= ~(1 << pin);
}

void GPIO_Write(volatile uint8_t *port, uint8_t pin, uint8_t val) {
    if (val)
        *port |= (1 << pin);
    else
        *port &= ~(1 << pin);
}

uint8_t GPIO_Read(volatile uint8_t *pin_reg, uint8_t pin) {
    return (*pin_reg & (1 << pin)) ? 1 : 0;
}