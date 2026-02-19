#include "StringModifier.h"

void StringModifier::Init() {

}

std::array<std::string, 2> StringModifier::ToDisplay(std::string toModify) {
    if (toModify.length() <= 16) {
        return {toModify, ""};
    }
    return {toModify.substr(0, 16), toModify.substr(16)};
}
