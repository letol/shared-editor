#include "editingmessage.h"

QUuid EditingMessage::getSenderSiteId() const {
    return senderSiteId;
}

int EditingMessage::getOperation() const {
    return op;
}

Symbol EditingMessage::getSymbol() const {
    return sym;
}

QDataStream &EditingMessage::serialize(QDataStream &stream) const {
    stream << op << sym << senderSiteId;
    return stream;
}

QDataStream &EditingMessage::unserialize(QDataStream &stream) {
    stream >> op >> sym >> senderSiteId;
    return stream;
}
