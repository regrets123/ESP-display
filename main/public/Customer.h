#ifndef ESP_INLAMNING_DISPLAY_CUSTOMER_H
#define ESP_INLAMNING_DISPLAY_CUSTOMER_H
#include <string>
#include <vector>

class Customer {
public:
    struct Data {
        std::string name;
        int price;
        std::vector<std::string> ads;
    };

private:
    std::vector<Data> customers;
};

#endif //ESP_INLAMNING_DISPLAY_CUSTOMER_H