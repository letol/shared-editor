//
// Created by leonardo on 07/05/19.
//

#include "Symbol.h"

Symbol::Symbol(char value, int siteId, int counter, std::vector<int> &fractIndex) {
    this->_value = value;
    this->_siteId = siteId;
    this->_counter = counter;
    this->_fractIndex = fractIndex;
}

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

char Symbol::getValue() {
    return _value;
}


