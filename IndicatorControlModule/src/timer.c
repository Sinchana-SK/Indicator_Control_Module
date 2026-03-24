#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint32_t system_time = 0;

ISR(TIMER0_COMPA_vect) {
    system_time++;
}

void Timer_Init() {
    TCCR0A |= (1 << WGM01);
    OCR0A = 249;

    TCCR0B |= (1 << CS01) | (1 << CS00);
    TIMSK0 |= (1 << OCIE0A);

    sei();
}

uint32_t Timer_GetTime() {
    return system_time;
}