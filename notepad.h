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

#include "networkserver.h"
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
    explicit Notepad(QWidget *parent = nullptr);
    ~Notepad();
signals:
    void showUpdateForm();
    void sendUri(const QString& uri);

public slots:
    void open(const QString& path);
    void newDocument();
    void updateButtonIcon(const QString& nameSurname,const QImage& image);

private slots:
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
    void remoteCharInsert(int siteId, QChar value, QTextCharFormat charFormat, QTextBlockFormat blockFormat, int index);
    void remoteCharDelete(int siteId, int index);
    void addRemoteUser(int siteId, User userInfo);
    void removeRemoteUser(int siteId);
    void remoteCursorPositionChanged(int siteId, int newPos);
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
    void pushUpdateButton();
    void getFileURI();

private:
    Ui::Notepad *ui;
    QString currentFile;
    QComboBox *comboStyle;
    QFontComboBox *comboFont;
    QComboBox *comboSize;
    QToolButton* updateButton;
    QLineEdit* uri;
    
    QToolBar *tb;
    QAction *actionTextColor;
    QAction *actionHighlight;
    
    NetworkServer server;
    SharedEditor sharedEditor;
    QVector<QColor> colors;
    QMap<int,RemoteUser> remoteUsers;
    TextEditorEventFilter *textEditorEventFilter;






};

#endif // NOTEPAD_H
