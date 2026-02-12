#ifndef ESP_DISPLAY_DECK_H
#define ESP_DISPLAY_DECK_H
#include <array>
#include <public/Customer.h>

class Deck {
public:
    const int costPerAds = 500;
    void Shuffle();
    Customer::Data* Draw();
    void InitDeck(std::array<Customer::Data, Customer::customerCount>* customers);

private:
    std::vector<Customer::Data*> ads;
    std::array<int, Customer::customerCount> adPerCustomer;
};

#endif //ESP_DISPLAY_DECK_H