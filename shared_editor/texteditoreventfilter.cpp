#include "texteditoreventfilter.h"
#include <QDebug>

bool TextEditorEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type()) {

    case QEvent::Resize:
        emit sizeChanged();
        break;

    case QEvent::Scroll:
        emit scrolled();
        break;

    default:
        break;
    }

    return QObject::eventFilter(obj, event);
}
