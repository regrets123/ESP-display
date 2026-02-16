#ifndef ESP_DISPLAY_DECK_H
#define ESP_DISPLAY_DECK_H
#include <array>
#include <vector>
#include "Customer.h"

class Deck {
public:
    const int costPerAds = 500;
    void Shuffle();
    Customer::Data* Draw();
    void CalcAds(std::array<Customer::Data, Customer::customerCount>* customers);

private:
    std::vector<Customer::Data*> ads;
    std::array<int, Customer::customerCount> adPerCustomer;
    std::array<Customer::Data, Customer::customerCount>* customers;
    int drawIndex = 0;
    int carryOver = -1;
};

#endif //ESP_DISPLAY_DECK_H