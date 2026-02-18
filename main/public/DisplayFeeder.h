#ifndef ESP_DISPLAY_DISPLAYFEEDER_H
#define ESP_DISPLAY_DISPLAYFEEDER_H
#include <hd44780.h>

#include <string>

#include "Deck.h"
#include "StringModifier.h"

#define SDA 13
#define SCL 14
#define LCD_I2C_ADDR 0x27  // PCF8574T (use 0x3F for PCF8574AT)
#define LCD_COLS 16
#define LCD_ROWS 2

class AdsTimer;

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

    hd44780_t lcd = {};
};

#endif
