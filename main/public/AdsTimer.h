#ifndef ESP_DISPLAY_ADS_TIMER_H
#define ESP_DISPLAY_ADS_TIMER_H
#include <cstdint>
#include "DisplayFeeder.h"


class AdsTimer {
public:
    void Init(DisplayFeeder* feederPtr);
    void Tick();

private:
    int64_t start;
    DisplayFeeder* feeder;
};

#endif // ESP_DISPLAY_ADS_TIMER_H