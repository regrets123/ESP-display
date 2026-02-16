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
    for (int round = 0; round < 100; round++)
    {
        deck.Shuffle();
        printf("--- Round %d ---\n", round);
        Customer::Data *ad;
        int i = 0;
        while ((ad = deck.Draw()) != nullptr)
        {
            printf("%d: %s\n", i++, ad->name.c_str());
        }
        vTaskDelay(1);
    }
}