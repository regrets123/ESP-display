#include "Customer.h"

std::array<Customer::Data, Customer::customerCount>* Customer::GetCustomers() {
    return &customers;
}

void Customer::InitCustomers() {
    customers[0] = {
        "Hederlige Harry",
        5000,
        {
                {"Köp bil hos Harry", scroll},
                {"En god bilaffär (för Harry!)", plainText},
                {"Hederlige Harrys Bilar", blink}
        }
    };
    customers[1] = {
        "Farmor Ankas Pajer AB",
        3000,
        {
                {"Köp paj hos Farmor Anka", scroll},
                {"Skynda innan Mårten ätit alla pajer", plainText}
        }
    };
    customers[2] = {
        "Svarte Petters Svartbyggen",
        1500,
        {
                {"Låt Petter bygga åt dig", scroll},
                {"Bygga svart? Ring Petter", plainText}
        }
    };
    customers[3] = {
        "Långbens detektivbyrå",
        4000,
        {
                {"Mysterier? Ring Långben", plainText},
                {"Långben fixar biffen", plainText}
        }
    };
    customers[4] = {
        "IoT 2025",
        1000,
        {
                {"Synas här? IOT:s Reklambyrå", plainText}
        }
    };
}
