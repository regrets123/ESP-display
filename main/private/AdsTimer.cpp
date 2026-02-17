#include "AdsTimer.h"
#include "esp_timer.h"

void AdsTimer::Init()
{
    start = esp_timer_get_time();
}

void AdsTimer::Tick()
{
        while (esp_timer_get_time() - start < 20000000LL) {
            current.update(); // scroll, animate, whatever the effect is
            vTaskDelay(pdMS_TO_TICKS(16));
        }
}