#include "StringModifier.h"
#include <cstdint>

void StringModifier::Init() {
}

std::string StringModifier::ParseSwedish(std::string text) {
    std::string result;
    result.reserve(text.size());

    for (size_t i = 0; i < text.size(); i++) {
        if ((unsigned char)text[i] == 0xC3 && i + 1 < text.size()) {
            switch ((unsigned char)text[i + 1]) {
                case 0xA5:
                    result += (char)CGRAM_SLOT_A_RING;
                    i++;
                    continue;  // å (custom CGRAM)
                case 0xA4:
                    result += (char)0xE1;
                    i++;
                    continue;  // ä
                case 0xB6:
                    result += (char)0xEF;
                    i++;
                    continue;  // ö
                case 0x85:
                    result += (char)CGRAM_SLOT_A_RING;
                    i++;
                    continue;  // Å (use å glyph)
                case 0x84:
                    result += (char)0xE1;
                    i++;
                    continue;  // Ä (use ä glyph)
                case 0x96:
                    result += (char)0xEF;
                    i++;
                    continue;  // Ö (use ö glyph)
            }
        }
        result += text[i];
    }

    return result;
}

std::array<std::string, 2> StringModifier::ToDisplay(std::string toModify) {
    std::string parsed = ParseSwedish(toModify);
    parsed.resize(32, ' ');  // pad to two full rows so stale LCD chars are overwritten
    return {parsed.substr(0, 16), parsed.substr(16, 16)};
}
