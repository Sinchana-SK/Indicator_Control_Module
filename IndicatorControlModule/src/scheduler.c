#include "scheduler.h"
#include "timer.h"
#include "app.h"

void Scheduler_Run() {
    static uint32_t last_100ms = 0;

    if (Timer_GetTime() - last_100ms >= 100) {
        last_100ms = Timer_GetTime();

        App_Task();   // main logic every 100 ms
    }
}