#include "DisplayFeeder.h"

void DisplayFeeder::Init(Deck *deck)
{
    this->deck = deck;
}

void DisplayFeeder::ExtractAd()
{
    if (deck != nullptr) {
        if(Customer::Data* data = deck->Draw()){
            // Example of displaying customer data
            // In a real application, this would be replaced with actual display logic
            // For example, sending data to an LCD or other display device
        }
    }
}

std::string DisplayFeeder::ShowAd(std::string adText, Customer::AdType type)
{
    
    return std::string();
}
