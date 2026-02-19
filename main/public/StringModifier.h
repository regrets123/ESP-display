#include <string>
#include <array>
#ifndef ESP_DISPLAY_STRINGMODIFIER_H
#define ESP_DISPLAY_STRINGMODIFIER_H

class StringModifier {
public:
    void Init ();
    std::array<std::string, 2> ToDisplay(std::string toModify);
    
private:
};

#endif // ESP_DISPLAY_STRINGMODIFIER_H