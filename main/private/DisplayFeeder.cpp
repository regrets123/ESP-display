#include "DisplayFeeder.h"
#include "StringModifier.h"

void DisplayFeeder::Init(Deck* deck, StringModifier* mod)
{
    this->deck = deck;
    this->stringFixer = mod;
    assert(deck);
}

void DisplayFeeder::ExtractAd()
{
    if (deck != nullptr) {
        currentCustomer = deck->Draw();
        currentAd = currentCustomer->ads[currentCustomer->lastAdIndex];
        currentCustomer->AdsShown();
    }
}

void DisplayFeeder::ShowAd()
{
    //based on StringModifier translating special characters and currentAds and Current customer we construct the string here and send it to the display.
}
