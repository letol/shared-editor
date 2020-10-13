#ifndef UPDATEFORM_H
#define UPDATEFORM_H

#include <QWidget>

namespace Ui {
class UpdateForm;
}

class UpdateForm : public QWidget
{
    Q_OBJECT

public:
    explicit UpdateForm(QWidget *parent = nullptr);
    ~UpdateForm();

private:
    Ui::UpdateForm *ui;
};

#endif // UPDATEFORM_H
