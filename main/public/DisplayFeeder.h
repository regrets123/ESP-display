#ifndef ESP_DISPLAY_DISPLAYFEEDER_H
#define ESP_DISPLAY_DISPLAYFEEDER_H
#include <string>

#include "Deck.h"
#include "StringModifier.h"

class DisplayFeeder {
   public:
    void Init(Deck* deck, StringModifier* mod, AdsTimer* timer, Customer* cust);
    void FetchNextAd();
    void ShowAd();
    Customer::Data* GetCustomer() { return currentCustomer; }
    Customer::Advertisement GetAd() { return currentAd; }

   private:
    Customer::Advertisement SelectAd();
    AdsTimer* timer;
    Deck* deck;
    Customer* customer;
    StringModifier* stringFixer;
    Customer::Data* currentCustomer;
    Customer::Advertisement currentAd;
    int edgeCaseCustIndex = 2;  // since only this customer has special case for when to view what ads, this will be sufficient.
};

#endif