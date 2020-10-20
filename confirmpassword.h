#ifndef CONFIRMPASSWORD_H
#define CONFIRMPASSWORD_H

#include <QDialog>
#include <QMap>

namespace Ui {
class ConfirmPassword;
}

class ConfirmPassword : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmPassword(QWidget *parent = nullptr);
    ~ConfirmPassword();
signals:
    void passwordData(const QString& pwd,const QString& pwdr);
public slots:
    void errorPwd();
private slots:
    void on_new_password_textChanged(const QString &arg1);
    void on_new_rpwd_textChanged(const QString &arg1);
    void on_pushButton_clicked();


    void on_pushButton_cancel_clicked();

    void on_pushButton_ok_clicked();

private:
    Ui::ConfirmPassword *ui;
    QMap<QString, bool> valid={{"pwd",false},
                              {"pwdR",false}};
    void checkValid(QMap<QString,bool> valid);
};

#endif // CONFIRMPASSWORD_H
