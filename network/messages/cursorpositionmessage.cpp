#include "cursorpositionmessage.h"

int CursorPositionMessage::getPos() {
    return pos;
}

QUuid CursorPositionMessage::getSiteId() {
    return siteId;
}

QDataStream &CursorPositionMessage::serialize(QDataStream &stream) const {
    stream << pos << siteId;
    return stream;
}

QDataStream &CursorPositionMessage::unserialize(QDataStream &stream) {
    stream >> pos >> siteId;
    return stream;
}
