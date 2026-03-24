#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h>

void GPIO_SetOutput(volatile uint8_t *ddr, uint8_t pin);
void GPIO_SetInput(volatile uint8_t *ddr, uint8_t pin);
void GPIO_Write(volatile uint8_t *port, uint8_t pin, uint8_t val);
uint8_t GPIO_Read(volatile uint8_t *pin_reg, uint8_t pin);

#endif