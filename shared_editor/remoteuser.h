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
    explicit RemoteUser(QTextEdit *textEditor, int siteId, QVector<QColor> *colors, User userInfo);
    int getSiteId();
    QColor getColor();
    QTextCursor* getCursor();
    void printCursor();
    User getUserInfo();

private:
    QTextEdit *textEditor;
    int siteId;
    QColor color;
    QTextCursor cursor;
    QFrame *cursorFrame;
    RemoteUserLabel *label;
    User userInfo;
};

#endif // REMOTEUSER_H
