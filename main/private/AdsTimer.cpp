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
    int64_t start = esp_timer_get_time();
    feeder->FetchNextAd();
    while (true) {
        if (esp_timer_get_time() - start >= 20000000LL) {
            start = esp_timer_get_time();
            feeder->FetchNextAd();
        }

        feeder->ShowAd();
        vTaskDelay(pdMS_TO_TICKS(16));
    }
}

int AdsTimer::IsEvenMinute() {  // 0 means even.
    int64_t elapsed = esp_timer_get_time() - start;
    return (elapsed / 60000000LL) % 2 == 0;
}