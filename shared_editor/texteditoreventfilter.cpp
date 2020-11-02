#include "texteditoreventfilter.h"
#include <QDebug>

bool TextEditorEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Resize) {
        sizeChanged();
        return QObject::eventFilter(obj, event);
    } else {
        return QObject::eventFilter(obj, event);
    }

}
