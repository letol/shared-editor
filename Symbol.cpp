//
// Created by leonardo on 07/05/19.
//

#include "Symbol.h"

int Symbol::getFractIndexDigit(int pos) const {
    int digit;
    try {
        digit = _fractIndex.at(pos);
    } catch (std::out_of_range& e) {
        return -1;
    }
    return digit;
}

std::vector<int> Symbol::getFractIndex() const {
    return _fractIndex;
}

int Symbol::getSiteId() {
    return _siteId;
}

size_t Symbol::fractIndexSize() {
    return _fractIndex.size();
}

QChar Symbol::getValue() {
    return _value;
}
