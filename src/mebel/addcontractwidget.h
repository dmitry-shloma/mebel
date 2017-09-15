#ifndef ADDCONTRACTWIDGET_H
#define ADDCONTRACTWIDGET_H

#include <QDialog>

namespace Ui {
class AddContractWidget;
}

class AddContractWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AddContractWidget(QDialog *parent = 0);
    ~AddContractWidget();

private slots:
    void on_cbCustomerType_currentIndexChanged(int index);

private:
    Ui::AddContractWidget *ui;
};

#endif // ADDCONTRACTWIDGET_H
