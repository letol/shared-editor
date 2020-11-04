#ifndef CONFIRMPASSWORDDIALOG_H
#define CONFIRMPASSWORDDIALOG_H

#include <QDialog>
#include <QMap>

namespace Ui {
class ConfirmPasswordDialog;
}

class ConfirmPasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmPasswordDialog(QWidget *parent = nullptr);
    ~ConfirmPasswordDialog();
signals:
    void passwordData(const QString& pwd,const QString& pwdNew);
public slots:
    void errorPwd(const QString& str);
    void updOK();
private slots:
    void on_new_password_textChanged(const QString &arg1);
    void on_new_rpwd_textChanged(const QString &arg1);
    void on_pushButton_cancel_clicked();
    void on_pushButton_ok_clicked();

private:
    Ui::ConfirmPasswordDialog *ui;
    QMap<QString, bool> valid={{"pwd",false},
                              {"pwdR",false}};
    void checkValid(QMap<QString,bool> valid);
};

#endif // CONFIRMPASSWORDDIALOG_H
