#ifndef ESP_DISPLAY_DISPLAYFEEDER_H
#define ESP_DISPLAY_DISPLAYFEEDER_H
#include "Deck.h"
#include <string>

class DisplayFeeder {
public:
    void Init(Deck* deck);
    void ExtractAd();
    std::string ShowAd(std::string adText, Customer::AdType type);

private:
    Deck* deck;
};

#endif