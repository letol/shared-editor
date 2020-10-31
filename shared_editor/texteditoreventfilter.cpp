#include "texteditoreventfilter.h"

bool TextEditorEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Resize) {
        sizeChanged();
        return QObject::eventFilter(obj, event);
    } else {
        return QObject::eventFilter(obj, event);
        /*if(event->type()==QEvent::MouseButtonPress){
            emit mouseEvent();
            return QObject::eventFilter(obj, event);
        }else{
            return QObject::eventFilter(obj, event);
        }*/
    }

}
