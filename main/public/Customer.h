#ifndef ESP_DISPLAY_CUSTOMER_H
#define ESP_DISPLAY_CUSTOMER_H
#include <array>
#include <string>
#include <vector>

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

#endif //ESP_DISPLAY_CUSTOMER_H
