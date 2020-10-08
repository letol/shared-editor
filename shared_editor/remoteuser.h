#ifndef REMOTEUSER_H
#define REMOTEUSER_H

#include <QTextEdit>
#include <QColor>
#include <QTextCursor>

#include "remoteuserlabel.h"

class RemoteUser
{
public:
    explicit RemoteUser(QTextEdit *textEditor, int siteId, QVector<QColor> *colors);
    int getSiteId();
    QColor getColor();
    QTextCursor* getCursor();
    void printCursor();

private:
    QTextEdit *textEditor;
    int siteId;
    QColor color;
    QTextCursor cursor;
    QFrame *cursorFrame;
    RemoteUserLabel *label;
};

#endif // REMOTEUSER_H
