#ifndef ESP_DISPLAY_CUSTOMER_H
#define ESP_DISPLAY_CUSTOMER_H
#include <array>
#include <string>
#include <vector>

class Customer {
   public:
    static constexpr int customerCount = 5;
    enum AdType { none,
                  scroll,
                  blink,
                  plainText,
                  maxNum };

    struct Advertisement {
        std::string text;
        AdType adType;
    };
    struct Data {
        std::string name;
        int price;
        std::vector<Advertisement> ads;
        int lastAdIndex = 0;
        void AdsShown() {
            lastAdIndex = (lastAdIndex + 1) % ads.size();
        }
    };
    std::array<Data, customerCount>* GetCustomers();
    void InitCustomers();
    Data* GetEdgeCaseCustomer() { return &customers[2]; }

   private:
    std::array<Data, customerCount> customers{};
};

#endif  // ESP_DISPLAY_CUSTOMER_H
