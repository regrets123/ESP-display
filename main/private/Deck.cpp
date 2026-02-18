#include "Deck.h"

#include "esp_random.h"

void Deck::Shuffle() {
    std::array<int, Customer::customerCount> remaining = adPerCustomer;
    int lastCustomer = -1;
    ads.clear();
    drawIndex = 0;

    // place the carried over customer first from previous shuffle
    if (carryOver >= 0) {
        ads.push_back(&(*customers)[carryOver]);
        lastCustomer = carryOver;
        carryOver = -1;
    }

    int totalRemaining = 0;
    for (int i = 0; i < Customer::customerCount; i++)
        totalRemaining += remaining[i];

    while (totalRemaining > 0) {
        // sum remaining ads for valid candidates (not the same as last placed)
        int validTotal = 0;
        for (int i = 0; i < Customer::customerCount; i++) {
            if (i != lastCustomer)
                validTotal += remaining[i];
        }

        // only the last customer has ads left, save for next shuffle
        if (validTotal == 0) {
            carryOver = lastCustomer;
            break;
        }

        // weighted random pick among valid candidates
        int pick = esp_random() % validTotal;
        int chosen = -1;
        for (int i = 0; i < Customer::customerCount; i++) {
            if (i != lastCustomer) {
                pick -= remaining[i];
                if (pick < 0) {
                    chosen = i;
                    break;
                }
            }
        }
        ads.push_back(&(*customers)[chosen]);
        remaining[chosen]--;
        totalRemaining--;
        lastCustomer = chosen;
    }
}

Customer::Data* Deck::Draw() {
    if (drawIndex >= ads.size())
        return nullptr;
    return ads[drawIndex++];
}

void Deck::CalcAds(std::array<Customer::Data, Customer::customerCount>* customers) {
    this->customers = customers;
    for (int i = 0; i < Customer::customerCount; i++) {
        adPerCustomer[i] = (*customers)[i].price / costPerAds;
    }
}
