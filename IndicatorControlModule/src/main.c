#include "timer.h"
#include "scheduler.h"
#include "app.h"
#include "uart.h"

int main(void) {

    Timer_Init();
    UART_Init(103); // 9600 baud
    App_Init();

    while (1) {
        Scheduler_Run();
    }
}