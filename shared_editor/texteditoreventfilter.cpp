#include "texteditoreventfilter.h"
#include "notepad.h"
#include <QDebug>

bool TextEditorEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Resize) {
        Notepad *notepad = qobject_cast<Notepad*>(parent());
        notepad->updateCursors(0);
    } else if (event->type() == QEvent::Wheel) {
        Notepad *notepad = qobject_cast<Notepad*>(parent());
        notepad->updateCursors(0);
    }

    return QObject::eventFilter(obj, event);
}
