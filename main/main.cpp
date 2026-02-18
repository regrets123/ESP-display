#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Customer.h"
#include "AdsTimer.h"
#include "Deck.h"

extern "C" void app_main(void) {
    Customer customer;
    customer.InitCustomers();
    Deck deck;
    Adstimer timer;
    timer.Init();
    deck.CalcAds(customer.GetCustomers());
    deck.Shuffle();
    printf("Shuffled deck:\n");

    

}