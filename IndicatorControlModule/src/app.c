#include "app.h"
#include "gpio.h"
#include "timer.h"
#include "uart.h"

#define LEFT_LED   PB1
#define RIGHT_LED  PB2
#define LEFT_BTN   PD7
#define RIGHT_BTN  PB0

typedef enum {
    IDLE,
    LEFT,
    RIGHT,
    HAZARD
} State;

State current_state = IDLE;

uint32_t last_toggle = 0;
uint8_t led_status = 0;

static uint32_t left_press_time = 0;
static uint32_t right_press_time = 0;
static uint8_t left_long_detected = 0;
static uint8_t right_long_detected = 0;
static uint8_t both_long_detected = 0;
static uint32_t both_press_start = 0;
static uint8_t prev_left = 0;
static uint8_t prev_right = 0;

void App_Init() {
    // LEDs
    GPIO_SetOutput(&DDRB, LEFT_LED);
    GPIO_SetOutput(&DDRB, RIGHT_LED);

    // Buttons
    GPIO_SetInput(&DDRD, LEFT_BTN);
    PORTD |= (1 << LEFT_BTN);

    GPIO_SetInput(&DDRB, RIGHT_BTN);
    PORTB |= (1 << RIGHT_BTN);
}

uint8_t button_pressed(volatile uint8_t *pin, uint8_t bit) {
    return !(*pin & (1 << bit));
}

void App_Task() {

    uint8_t left = button_pressed(&PIND, LEFT_BTN);
    uint8_t right = button_pressed(&PINB, RIGHT_BTN);

    uint32_t now = Timer_GetTime();

    // Detect when both become pressed
    if (left && right && !(prev_left && prev_right)) {
        both_press_start = now;
    }

    // Reset detected on release
    if (!left) {
        left_long_detected = 0;
        left_press_time = 0;
    }
    if (!right) {
        right_long_detected = 0;
        right_press_time = 0;
    }
    if (!left || !right) {
        both_long_detected = 0;
        both_press_start = 0;
    }

    // Detect press
    if (left && left_press_time == 0) left_press_time = now;
    if (right && right_press_time == 0) right_press_time = now;

    // State transitions on long press
    if (left && (now - left_press_time >= 1000) && !left_long_detected) {
        left_long_detected = 1;
        if (current_state == IDLE) {
            current_state = LEFT;
        } else if (current_state == LEFT) {
            current_state = IDLE;
        } else if (current_state == RIGHT) {
            current_state = LEFT;
        } else if (current_state == HAZARD) {
            current_state = IDLE;
        }
    }

    if (right && (now - right_press_time >= 1000) && !right_long_detected) {
        right_long_detected = 1;
        if (current_state == IDLE) {
            current_state = RIGHT;
        } else if (current_state == RIGHT) {
            current_state = IDLE;
        } else if (current_state == LEFT) {
            current_state = RIGHT;
        } else if (current_state == HAZARD) {
            current_state = IDLE;
        }
    }

    if (left && right && (now - both_press_start >= 1000) && !both_long_detected) {
        both_long_detected = 1;
        current_state = HAZARD;
        UART_SendString("HAZARD ON\n");
    }

    // Update prev
    prev_left = left;
    prev_right = right;

    // Blinking every 300 ms
    if (now - last_toggle >= 300) {
        last_toggle = now;
        led_status ^= 1;

        switch (current_state) {
            case LEFT:
                GPIO_Write(&PORTB, LEFT_LED, led_status);
                GPIO_Write(&PORTB, RIGHT_LED, 0);
                break;

            case RIGHT:
                GPIO_Write(&PORTB, RIGHT_LED, led_status);
                GPIO_Write(&PORTB, LEFT_LED, 0);
                break;

            case HAZARD:
                GPIO_Write(&PORTB, LEFT_LED, led_status);
                GPIO_Write(&PORTB, RIGHT_LED, led_status);
                break;

            default:
                GPIO_Write(&PORTB, LEFT_LED, 0);
                GPIO_Write(&PORTB, RIGHT_LED, 0);
        }
    }
}