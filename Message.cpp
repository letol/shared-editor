//
// Created by leonardo on 07/05/19.
//

#include "Message.h"

int Message::getSenderSiteId() {
    return _sender;
}

int Message::getOperation() const {
    return _op;
}

Symbol Message::getSymbol() const {
    return _sym;
}


