#include "Deck.h"
#include "esp_random.h"

void Deck::Shuffle() {
    std::array<int, Customer::customerCount> remaining = adPerCustomer;
    int lastCustomer = -1;
    ads.clear();

    int totalRemaining = 0;
    for (int i = 0; i < Customer::customerCount; i++)
        totalRemaining += remaining[i];

    while (totalRemaining > 0) {
        // find the customer with the most remaining ads that isn't the last placed
        int best = -1;
        for (int i = 0; i < Customer::customerCount; i++) {
            if (remaining[i] > 0 && i != lastCustomer && (best == -1 || remaining[i] > remaining[best]))
                best = i;
        }
        // among candidates with equal count, pick randomly for variety
        int tiedCount = 0;
        for (int i = 0; i < Customer::customerCount; i++) {
            if (remaining[i] == remaining[best] && i != lastCustomer)
                tiedCount++;
        }
        int pick = esp_random() % tiedCount;
        for (int i = 0; i < Customer::customerCount; i++) {
            if (remaining[i] == remaining[best] && i != lastCustomer) {
                if (pick == 0) { best = i; break; }
                pick--;
            }
        }

        ads.push_back(&(*customers)[best]);
        remaining[best]--;
        totalRemaining--;
        lastCustomer = best;
    }
}

Customer::Data * Deck::Draw() {
    return  nullptr;
}

void Deck::CalcAds(std::array<Customer::Data, Customer::customerCount>* customers) {
    this->customers = customers;
    for(int i = 0; i < Customer::customerCount; i++) {
        adPerCustomer[i] = customers[i].data()->price / costPerAds;
    }
}
