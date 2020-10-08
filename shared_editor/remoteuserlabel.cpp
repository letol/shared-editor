#include <QTimer>

#include "remoteuserlabel.h"

void RemoteUserLabel::enterEvent(QEvent *event)
{
    if (!mouseOver) {
        mouseOver = true;
        hide();
        QTimer::singleShot(3000, this, [=](){
            show();
            mouseOver = false;
        });
    }
}

bool RemoteUserLabel::isMouseOver()
{
    return mouseOver;
}
