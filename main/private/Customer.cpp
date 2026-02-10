#include "Customer.h"


/*Svarte Petters Svartbyggen:
Betalat 1500. Vill visa
"Låt Petter bygga åt dig" (scroll) - på jämna minuter
"Bygga svart? Ring Petter" text - på ojämna minuter


Långbens detektivbyrå:
Betalat 4000. Vill visa
"Mysterier? Ring Långben" text
"Långben fixar biffen" text

Ibland måste vi visa reklam för oss själva:
Vi ger oss själva tid motsvarande 1000 kr.
Meddelande "Synas här? IOT:s Reklambyrå" text#1#*/

void Customer::InitCustomers() {
    Data customer0;
    customer0.name = "Hederlige Harry";
    customer0.price = 5000;
    customer0.ads.push_back({.text = "Köp bil hos Harry", .adType = scroll});
    customer0.ads.push_back({.text = "En god bilaffär (för Harry!)", .adType = plainText});
    customer0.ads.push_back({.text = "Hederlige Harrys Bilar", .adType = blink});
    customers[0] = customer0;

    Data customer1;
    customer1.name = "Farmor Ankas Pajer AB";
    customer1.price = 3000;
    customers[1] = customer1;
    customer1.ads.push_back({"Köp paj hos Farmor Anka", scroll});
    customer1.ads.push_back({"Skynda innan Mårten ätit alla pajer", plainText});

    Data customer2;
    customer2.name = "Svarte Petters Svartbyggen";
    customer2.price = 1500;
    customers[2] = customer2;
    customer2.ads.push_back({"Låt Petter bygga åt dig", scroll}); // på jämna minuter
    customer2.ads.push_back({"Bygga svart? Ring Petter", plainText}); // på ojämna minuter
}