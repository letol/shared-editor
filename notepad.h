#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>

#include "NetworkServer.h"
#include "SharedEditor.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Notepad;
}
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    explicit Notepad(QWidget *parent = nullptr);
    ~Notepad();

// TO BE REMOVED
protected:
    void timerEvent(QTimerEvent *event) override;

private slots:
    void newDocument();
    void open();
    void save();
    void saveAs();
    void print();
    void exit();
    void copy();
    void cut();
    void paste();
    void undo();
    void redo();
    void selectFont();
    void setFontBold(bool bold);
    void setFontUnderline(bool underline);
    void setFontItalic(bool italic);
    void about();
    void localChange();
    void remoteChange();

private:
    Ui::Notepad *ui;
    QString currentFile;
    NetworkServer server;
    SharedEditor sharedEditor;
    SharedEditor fakeRemoteEditor; // TO BE REMOVED
    QChar fakeRemoteChar; // TO BE REMOVED
};

#endif // NOTEPAD_H
