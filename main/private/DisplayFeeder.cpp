#include "DisplayFeeder.h"

#include "AdsTimer.h"
#include "StringModifier.h"

void DisplayFeeder::Init(Deck* deck, StringModifier* mod, AdsTimer* timer, Customer* cust) {
    this->deck = deck;
    this->stringFixer = mod;
    this->timer = timer;
    this->customer = cust;
    assert(this->deck);
    assert(this->stringFixer);
    assert(this->timer);
    assert(this->customer);
}

void DisplayFeeder::FetchNextAd() {
    if (deck) {
        currentCustomer = deck->Draw();
        currentAd = SelectAd();
        currentCustomer->AdsShown();
    }
}

void DisplayFeeder::ShowAd() {
    std::string fixed = stringFixer->ToDisplay(currentAd.text);
}

Customer::Advertisement DisplayFeeder::SelectAd() {
    int indexToUse = -1;
    if (currentCustomer && currentCustomer == (customer->GetEdgeCaseCustomer())) {
        indexToUse = timer->IsEvenMinute();
    } else {
        indexToUse = currentCustomer->lastAdIndex;
    }
    return currentCustomer->ads[indexToUse];
}
