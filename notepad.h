#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QToolButton>
#include <QLineEdit>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QWidgetAction>
#include <QMessageBox>
#include <QFont>
#include <QFontDialog>
#include <QDebug>
#include <QTextBlock>
#include <QPainter>
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QColorDialog>
#include <QComboBox>
#include <QPushButton>
#include <QFontComboBox>
#include <QTextBlockFormat>
#include <QFileInfo>
#include <QFontDatabase>
#include <QMenu>
#include <QMenuBar>
#include <QTextCodec>
#include <QTextEdit>
#include <QStatusBar>
#include <QToolBar>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QTextList>
#include <QCloseEvent>
#include <QMimeData>
#include <QMimeDatabase>
#include <QLabel>

#include "sharededitor.h"
#include "remoteuser.h"
#include "texteditoreventfilter.h"



QT_BEGIN_NAMESPACE
namespace Ui {
class Notepad;
}

class QAction;
class QComboBox;
class QFontComboBox;
class QTextCharFormat;
class QTextDocument;
class QMenu;
class QLabel;

QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    explicit Notepad(QUuid siteId, QWidget *parent = nullptr);
    ~Notepad();
    SharedEditor* getSharedEditor();

signals:
    void showUpdateForm();
    //void showOnlineUsersForm();
    void newDocument(const QVector<Symbol>& symbols, const QString& name);
    void fileClosed();
    void newCursorPosition(int pos);
    void logout();

public slots:
    void openExistingDocument(const QVector<Symbol>& symbols, QString name);
    void openNewDocument(const QString& name);
    void updateButtonIcon(const QString& nameSurname,const QImage& image);
    void remoteCursorPositionChanged(QUuid siteId, int newPos);

private slots:
    void changeFile();
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
    void remoteCharInsert(QUuid siteId, QChar value, QTextCharFormat charFormat, QTextBlockFormat blockFormat, int index);
    void remoteCharDelete(QUuid siteId, int index);
    void addRemoteUser(QUuid siteId, User userInfo);
    void removeRemoteUser(QUuid siteId);
    void localCursorPositionChanged();
    void on_actionExport_PDF_triggered();
    void on_actionAt_left_triggered();
    void on_actionCentered_triggered();
    void on_actionAt_right_triggered();
    void on_action6_triggered();
    void on_action36_triggered();
    void on_action7_triggered();
    void on_action8_triggered();
    void on_action9_triggered();
    void on_action10_triggered();
    void on_action11_triggered();
    void on_action12_triggered();
    void on_action14_triggered();
    void on_action24_triggered();
    void on_action18_triggered();
    void size(const QString &text);
    void font(const QFont &f);
    void style(int styleIndex);
    void textColor();
    void colorChanged(const QColor &c);
    void textHighlight();
    void updateCursors();
    void onlineUsersTriggered();
    void setLocalUser(const User &user);
    void pushUpdateButton();

public:

     QMap<int,RemoteUser> remoteUsers; //da sposatare
private:
    Ui::Notepad *ui;
    QComboBox *comboStyle;
    QFontComboBox *comboFont;
    QComboBox *comboSize;
    QToolButton* updateButton;

    
    QToolBar *tb;
    QAction *actionTextColor;
    QAction *actionHighlight;
    
    SharedEditor sharedEditor;
    QVector<QColor> colors;

    QMap<QUuid,RemoteUser> remoteSites;
    QMap<QString,QColor> remoteUserColors;
    TextEditorEventFilter *textEditorEventFilter;

};

#endif // NOTEPAD_H
