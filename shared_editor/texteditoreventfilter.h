#ifndef TEXTEDITOREVENTFILTER_H
#define TEXTEDITOREVENTFILTER_H

#include <QObject>
#include <QEvent>
#include <QTextEdit>

class TextEditorEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit TextEditorEventFilter(QObject *parent = nullptr) : QObject(parent) {};

signals:
    void sizeChanged();
    void scrolled();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // TEXTEDITOREVENTFILTER_H
