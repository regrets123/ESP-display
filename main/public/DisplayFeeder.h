#ifndef ESP_DISPLAY_DISPLAYFEEDER_H
#define ESP_DISPLAY_DISPLAYFEEDER_H
#include "Deck.h"
#include <string>
#include "StringModifier.h"

class DisplayFeeder {
public:
    void Init(Deck* deck, StringModifier* mod);
    void ExtractAd();
    void ShowAd();
    Customer::Data* GetCustomer() { return currentCustomer; }
    Customer::Advertisement GetAd() { return currentAd; }

private:
    Deck* deck;
    StringModifier* stringFixer;
    Customer::Data* currentCustomer;
    Customer::Advertisement currentAd;
};

#endif