#include "texteditoreventfilter.h"

bool TextEditorEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Resize) {
        sizeChanged();
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
}
