#include "AdsTimer.h"

#include <Customer.h>

#include "DisplayFeeder.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char* TAG = "AdsTimer";

void AdsTimer::Init(DisplayFeeder* feederPtr) {
    assert(feederPtr);
    feeder = feederPtr;
}

void AdsTimer::Tick() {
    bootTime = esp_timer_get_time();
    start = bootTime;
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

int AdsTimer::IsEvenMinute() {  // returns 0 on even minute (ads[0]), 1 on odd minute (ads[1])
    int64_t elapsed = esp_timer_get_time() - bootTime;
    int isEven = (elapsed / 60000000LL) % 2 != 0;
    ESP_LOGI(TAG, "IsEvenMinute: elapsed=%" PRId64 "us, minute=%lld, isEven=%d",
             elapsed, elapsed / 60000000LL, isEven);
    return isEven;
}