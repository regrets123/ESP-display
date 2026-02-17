#ifndef ESP_DISPLAY_ADS_TIMER_H
#define ESP_DISPLAY_ADS_TIMER_H
#include <cstdint>


class AdsTimer {
public:
    void Init();
    void Tick();


private:
    int64_t start;
};

#endif // ESP_DISPLAY_ADS_TIMER_H