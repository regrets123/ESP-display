#include <string>
#include <array>
#ifndef ESP_DISPLAY_STRINGMODIFIER_H
#define ESP_DISPLAY_STRINGMODIFIER_H

class StringModifier {
public:
    static constexpr uint8_t CGRAM_SLOT_A_RING = 1;  // å/Å custom character slot

    void Init ();
    std::array<std::string, 2> ToDisplay(std::string toModify);
    std::string ParseSwedish(std::string text);
    
private:
};

#endif // ESP_DISPLAY_STRINGMODIFIER_H