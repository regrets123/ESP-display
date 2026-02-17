#include <string>
#ifndef ESP_DISPLAY_STRINGMODIFIER_H
#define ESP_DISPLAY_STRINGMODIFIER_H

class StringModifier {
public:
    void Init ();
    std::string ToDisplay(std::string toModify);
    
private:
};

#endif // ESP_DISPLAY_STRINGMODIFIER_H