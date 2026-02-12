#include "Deck.h"

void Deck::Shuffle() {
}

Customer::Data * Deck::Draw() {
    return  nullptr;
}

void Deck::InitDeck(std::array<Customer::Data, Customer::customerCount>* customers) {
    int totalprice = 0;
    for(int i = 0; i < Customer::customerCount; i++) {
        totalprice += customers[i].data()->price;
    }
    int totalAds = totalprice / costPerAds;
    ads.resize(totalAds);
    for(int i = 0; i < totalAds; i++) {
        adPerCustomer[i] = totalprice / customers[i].data()->price;
    }
    for(int i = 0; i < Customer::customerCount; i++) {
        ads.insert(ads.end(), adPerCustomer[i], customers[i].data());
    }
}
