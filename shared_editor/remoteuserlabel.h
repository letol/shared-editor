#ifndef REMOTEUSERLABEL_H
#define REMOTEUSERLABEL_H

#include <QLabel>

class RemoteUserLabel : public QLabel
{
public:
    RemoteUserLabel(const QString &text, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()) :
        QLabel(text, parent, f) {};

    void enterEvent(QEvent *event) override;
    bool isMouseOver();

private:
    bool mouseOver = false;
};

#endif // REMOTEUSERLABEL_H
