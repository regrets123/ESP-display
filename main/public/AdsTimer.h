#ifndef ESP_DISPLAY_ADS_TIMER_H
#define ESP_DISPLAY_ADS_TIMER_H
#include <cstdint>

class DisplayFeeder;

class AdsTimer {
   public:
    void Init(DisplayFeeder* feederPtr);
    void Tick();

    int IsEvenMinute();

   private:
    int64_t start;
    DisplayFeeder* feeder;
};

#endif  // ESP_DISPLAY_ADS_TIMER_H