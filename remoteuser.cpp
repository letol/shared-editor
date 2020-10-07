#include <QPropertyAnimation>

#include "remoteuser.h"

RemoteUser::RemoteUser(QTextEdit *textEditor, int siteId, QVector<QColor> *colors) :
    textEditor(textEditor),
    siteId(siteId),
    cursor(QTextCursor(textEditor->document()))
{
    color = colors->at(siteId % colors->size());
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColorConstants::White);
    pal.setColor(QPalette::WindowText, color);

    //Visible cursor init
    cursorFrame = new QFrame(textEditor);
    cursorFrame->setFrameStyle(QFrame::VLine | QFrame::Plain);
    cursorFrame->setLineWidth(3);
    cursorFrame->setPalette(pal);

    //Cursor blinking
    QPropertyAnimation *blink = new QPropertyAnimation(cursorFrame, "lineWidth");
    blink->setDuration(1000);
    blink->setStartValue(3);
    blink->setEndValue(0);
    blink->setLoopCount(-1);
    blink->setEasingCurve(QEasingCurve::InOutExpo);
    blink->start(QPropertyAnimation::DeleteWhenStopped);

    //Label init
    label = new RemoteUserLabel("remote_user", textEditor); //TODO: change with nickname
    label->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    label->setAutoFillBackground(true);
    label->setPalette(pal);
    label->setMouseTracking(true);
}

int RemoteUser::getSiteId()
{
    return siteId;
}

QColor RemoteUser::getColor()
{
    return color;
}

QTextCursor* RemoteUser::getCursor()
{
    return &cursor;
}

void RemoteUser::printCursor()
{
    QRect curRect = textEditor->cursorRect(cursor);
    if (!cursorFrame->isVisible()) {
        cursorFrame->setVisible(true);
    }
    //curRect.adjust(-2,0,0,0);
    cursorFrame->setGeometry(curRect);
    cursorFrame->raise();

    QSize labelSize = label->size();
    QPoint labelAnchor = curRect.bottomLeft();

    if (labelAnchor.y() + labelSize.height() > textEditor->height()) {
        labelAnchor = curRect.topLeft();
        labelAnchor.ry() -= labelSize.height();
    }

    if (labelAnchor.x() + labelSize.width() > textEditor->width()) {
        labelAnchor.rx() -= labelSize.width();
    }

    label->move(labelAnchor);

    if (!label->isMouseOver()) {
        label->show();
    }
}
