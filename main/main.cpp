#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Customer.h"
#include "Deck.h"

extern "C" void app_main(void)
{
    printf("Hello from ESP32!\n");

    while(true) {
        printf("ESP32 is running...\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay 1 second
    }
}