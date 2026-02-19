#include "StringModifier.h"

void StringModifier::Init() {
}

std::string StringModifier::ParseSwedish(std::string text) {
    std::string result;
    result.reserve(text.size());

    for (size_t i = 0; i < text.size(); i++) {
        if ((unsigned char)text[i] == 0xC3 && i + 1 < text.size()) {
            switch ((unsigned char)text[i + 1]) {
                case 0xA5:
                    result += (char)0xE5;
                    i++;
                    continue;  // å
                case 0xA4:
                    result += (char)0xE4;
                    i++;
                    continue;  // ä
                case 0xB6:
                    result += (char)0xF6;
                    i++;
                    continue;  // ö
                case 0x85:
                    result += (char)0xC5;
                    i++;
                    continue;  // Å
                case 0x84:
                    result += (char)0xC4;
                    i++;
                    continue;  // Ä
                case 0x96:
                    result += (char)0xD6;
                    i++;
                    continue;  // Ö
            }
        }
        result += text[i];
    }

    return result;
}

std::array<std::string, 2> StringModifier::ToDisplay(std::string toModify) {
    std::string parsed = ParseSwedish(toModify);
    if (parsed.length() <= 16) {
        return {toModify, ""};
    }
    return {parsed.substr(0, 16), parsed.substr(16)};
}
