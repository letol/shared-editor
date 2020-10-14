#ifndef UPDATEFORM_H
#define UPDATEFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QFileDialog>
#include "confirmpassword.h"

namespace Ui {
class UpdateForm;
}

class UpdateForm : public QWidget
{
    Q_OBJECT

public:
    explicit UpdateForm(QWidget *parent = nullptr);
    ~UpdateForm();

private slots:
    void on_pushButto_nome_clicked();
    void changeName();
    void changeCognome();

    void on_pushButton_cognome_clicked();

    void on_pushButton_image_clicked();

    void on_button_password_clicked();

private:
    Ui::UpdateForm *ui;
    QLineEdit *lineNome;
    QLineEdit *lineCognome;
};

#endif // UPDATEFORM_H
