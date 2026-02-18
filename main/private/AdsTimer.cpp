#include "AdsTimer.h"

#include <Customer.h>

#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void AdsTimer::Init(DisplayFeeder* feederPtr) {
    assert(feederPtr);
    feeder = feederPtr;
}

void AdsTimer::Tick() {
    int64_t start_time = esp_timer_get_time();
    feeder->FetchNextAd();
    while (true) {
        if (esp_timer_get_time() - start_time >= 20000000LL) {
            start_time = esp_timer_get_time();
            feeder->FetchNextAd();
        }

        feeder->ShowAd();
        vTaskDelay(pdMS_TO_TICKS(16));
    }
}