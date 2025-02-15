#include <QPropertyAnimation>

#include "remoteuser.h"

RemoteUser::RemoteUser(QTextEdit *textEditor, QUuid siteId, QColor color, User userInfo) :
    textEditor(textEditor),
    siteId(siteId),
    color(color),
    cursor(QTextCursor(textEditor->document())),
    userInfo(userInfo)
{
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
    label = new RemoteUserLabel(userInfo.getNickname(), textEditor);
    label->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    label->setAutoFillBackground(true);
    label->setPalette(pal);
    label->setMouseTracking(true);
}

QUuid RemoteUser::getSiteId()
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
    curRect.adjust(-1,0,1,0);
    cursorFrame->setGeometry(curRect);
    cursorFrame->raise();

    if (printingLabel) printLabel();
}

void RemoteUser::printLabel()
{
    printingLabel = true;
    QRect curRect = textEditor->cursorRect(cursor);
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
        label->raise();
    }
}

void RemoteUser::hideCursor()
{
    label->close();
    cursorFrame->close();
}

void RemoteUser::hideLabel()
{
    printingLabel = false;
    label->close();
}

User RemoteUser::getUserInfo()
{
    return userInfo;
}
