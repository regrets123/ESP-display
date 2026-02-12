#ifndef ESP_INLAMNING_DISPLAY_CUSTOMER_H
#define ESP_INLAMNING_DISPLAY_CUSTOMER_H
#include <array>
#include <string>
#include <vector>

/* En kund som betalat 10000
kr få ungefär dubbelt så många visningar som en som betalar 5000 kr etc.
Varje visning räcker 20 sekunder. Sen slumpas nästa fram - viktigt: ALDRIG
SAMMA KUND TVÅ GÅNGER PÅ RAKEN*/



class Customer {
public:
    static constexpr int customerCount = 5;
    enum AdType {none, scroll, blink, plainText, maxNum};
    struct Advertisement {
        std::string text;
        AdType adType;
    };
    struct Data {
        std::string name;
        int price;
        std::vector<Advertisement> ads;
    };
    std::array<Data, customerCount>* GetCustomers();
    void InitCustomers();
private:
    std::array<Data, customerCount> customers{};

};


#endif //ESP_INLAMNING_DISPLAY_CUSTOMER_H
