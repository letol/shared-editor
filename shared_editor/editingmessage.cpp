//
// Created by leonardo on 07/05/19.
//

#include "editingmessage.h"

int EditingMessage::getSenderSiteId() {
    return _sender;
}

int EditingMessage::getOperation() const {
    return _op;
}

Symbol EditingMessage::getSymbol() const {
    return _sym;
}


