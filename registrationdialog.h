#ifndef REGISTRATIONDIALOG_H
#define REGISTRATIONDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "user.h"


namespace Ui {
class RegistrationDialog;
}

class RegistrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationDialog(QWidget *parent = nullptr);
    ~RegistrationDialog();

signals:
    void registratationData(const User &user);

public slots:
    void errorHeadling(const QString &str);
    void close();

private slots:
    void on_pushButton_image_clicked();
    void on_pushButton_clicked();
    void on_lineEdit_name_textChanged();

    void on_lineEdit_surname_textChanged();

    void on_lineEdit_nickname_textChanged();

    void on_lineEdit_email_textChanged();

    void on_lineEdit_password_textChanged(const QString &arg1);

    void on_lineEdit_pwdrepeat_textChanged(const QString &arg1);


private:
    Ui::RegistrationDialog *ui;

    QMap<QString, bool> valid={{"name", false},
                               {"surname", false},
                               {"nickname", false},
                               {"email",false},
                               {"pwd",false},
                              {"pwdR",false}};
   void checkValid(QMap<QString,bool> valid);

};

#endif // REGISTRATIONDIALOG_H
