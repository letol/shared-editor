#ifndef MESSAGE_H
#define MESSAGE_H

#include "symbol.h"

#define MSG_INSERT  0
#define MSG_ERASE   1

class EditingMessage {
private:
    Symbol _sym;
    int _op;
    int _sender;

public:
    EditingMessage(Symbol &sym, int op, int senderSiteId) :
        _sym(sym),
        _op(op),
        _sender(senderSiteId) {};

    int getSenderSiteId();
    int getOperation() const;
    Symbol getSymbol() const;
};


#endif //MESSAGE_H
