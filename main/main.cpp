#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Customer.h"
#include "Deck.h"

extern "C" void app_main(void)
{
    Customer customer;
    customer.InitCustomers();

    Deck deck;
    deck.CalcAds(customer.GetCustomers());
    deck.Shuffle();

    printf("Shuffled deck:\n");
    for (int i = 0; i < 29; i++) {
        Customer::Data* ad = deck.Draw();
        if (ad)
            printf("%d: %s\n", i, ad->name.c_str());
    }
}