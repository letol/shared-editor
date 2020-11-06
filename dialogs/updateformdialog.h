#ifndef UPDATEFORMDIALOG_H
#define UPDATEFORMDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <user.h>

namespace Ui {
class UpdateFormDialog;
}

class UpdateFormDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateFormDialog(QWidget *parent = nullptr);
    ~UpdateFormDialog();
signals:
    void showCP();
    void nameChange(const QString& name);
    void surnameChange(const QString& surname);
    void imageChange(const QByteArray& image);
    void logout();
public slots:
    void updateOK(const User& user);
    void updateKO(const QString& str);
    void userLogged(const User& userL);
private slots:
    void on_imageChange_clicked();

    void on_passwordChange_clicked();

    void on_nameChange_clicked();

    void on_surnameChange_clicked();
    void changeName();
    void changeCognome();
    void on_logout_clicked();

private:
    Ui::UpdateFormDialog *ui;
    User user;
    QLineEdit *lineName;
    QLineEdit *lineSurname;

};

#endif // UPDATEFORMDIALOG_H
