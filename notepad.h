#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QToolButton>

#include "networkserver.h"
#include "sharededitor.h"
#include "remoteuser.h"
#include "texteditoreventfilter.h"
#include "logindialog.h"
#include "socketclient.h"
#include "messageType.h"
#include "openfiledialog.h"
#include "updateformdialog.h"


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

// TO BE REMOVED
protected:
    void timerEvent(QTimerEvent *event) override;


signals:
     void errorLogin(const QString& str);
     void regClose();
     void errorReg(const QString& str);
     void udpKO(const QString& str);
     void pwdKO(const QString& str);
     void userIsChanged(const User& user);
     void userLogged(const User& user);
public slots:
    void open(const QString& path);
    void newDocument();
    void loginData(const User& user);
    void regData(const User& user);



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
    void showUpdateForm();

    void regOK(const User& user);
    void regKO();
    void logOK(const User& user);
    void logKO();
    void errorDB();
    void notLogged();
    void updateOK(const User& user);
    void updeteKO();
    void errorPwd();
    void pwdChanged(const QString& pwd,const QString& pwdNew);
    void nameChanged(const QString& name);
    void surnameChanged(const QString& surname);
    void imageChanged(const QByteArray& image);




private:
    Ui::Notepad *ui;
    QString currentFile;
    QComboBox *comboStyle;
    QFontComboBox *comboFont;
    QComboBox *comboSize;
    QToolButton* updateButton;
    
    QToolBar *tb;
    QAction *actionTextColor;
    QAction *actionHighlight;
    
    NetworkServer server;
    SharedEditor sharedEditor;
    SharedEditor fakeRemoteEditor; // TO BE REMOVED
    QChar fakeRemoteChar; // TO BE REMOVED
    SharedEditor fakeRemoteEditor2; // TO BE REMOVED
    QChar fakeRemoteChar2; // TO BE REMOVED
    QVector<QColor> colors;
    QMap<int,RemoteUser> remoteUsers;
    TextEditorEventFilter *textEditorEventFilter;

    LoginDialog *logindialog;
    OpenFileDialog *openfile;
    UpdateFormDialog *updateForm;
    User currentUser;

    SocketClient socket;


};

#endif // NOTEPAD_H
