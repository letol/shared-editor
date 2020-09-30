#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QTextDocument>

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
    void setHighlightOwners(bool highlightOwners);
    void about();
    void localChange(int position, int charsRemoved, int charsAdded);
    void remoteCharInsert(int siteId, QChar value, int index);
    void remoteCharDelete(int siteId, int index);
    void addRemoteUser(int siteId);
    void removeRemoteUser(int siteId);
    void remoteCursorPositionChanged(int siteId, int newPos);

private:
    Ui::Notepad *ui;
    NetworkServer server;
    SharedEditor sharedEditor;
    SharedEditor fakeRemoteEditor; // TO BE REMOVED
    QChar fakeRemoteChar; // TO BE REMOVED
    QMap<int,QTextCursor> remoteUserCursors;
    QVector<QColor> colors;
    QMap<int,QColor> remoteUserColors;
};

#endif // NOTEPAD_H
