#ifndef ADDORDERWIDGET_H
#define ADDORDERWIDGET_H

#include <QDialog>

namespace Ui {
class AddOrderWidget;
}

class AddOrderWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AddOrderWidget(QDialog *parent = 0);
    ~AddOrderWidget();

private slots:
    void on_cbCustomerType_activated(int index);

private:
    Ui::AddOrderWidget *ui;
};

#endif // ADDORDERWIDGET_H
