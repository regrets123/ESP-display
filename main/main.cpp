#include <i2cdev.h>
#include <stdio.h>

#include "AdsTimer.h"
#include "Customer.h"
#include "Deck.h"
#include "DisplayFeeder.h"
#include "StringModifier.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void app_main(void) {
    ESP_ERROR_CHECK(i2cdev_init());
    Customer customer;
    customer.InitCustomers();
    Deck deck;
    StringModifier sMod;
    DisplayFeeder feeder;
    AdsTimer timer;
    feeder.Init(&deck, &sMod, &timer, &customer);
    timer.Init(&feeder);

    deck.CalcAds(customer.GetCustomers());
    deck.Shuffle();
    printf("Shuffled deck:\n");
    timer.Tick();
}
