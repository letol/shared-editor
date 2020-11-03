#ifndef REMOTEUSER_H
#define REMOTEUSER_H

#include <QTextEdit>
#include <QColor>
#include <QTextCursor>

#include "remoteuserlabel.h"
#include "user.h"

class RemoteUser
{
public:
    explicit RemoteUser(QTextEdit *textEditor, QUuid siteId, QColor color, User userInfo);
    QUuid getSiteId();
    QColor getColor();
    QTextCursor* getCursor();
    void printCursor();
    void printLabel();
    void hideCursor();
    void hideLabel();
    User getUserInfo();

private:
    QTextEdit *textEditor;
    QUuid siteId;
    QColor color;
    QTextCursor cursor;
    QFrame *cursorFrame;
    RemoteUserLabel *label;
    User userInfo;
    bool printingLabel = false;
};

#endif // REMOTEUSER_H
