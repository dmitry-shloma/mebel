#ifndef ORDERWIDGET_H
#define ORDERWIDGET_H

#include <QDialog>

namespace Ui {
class OrderWidget;
}

class OrderWidget : public QDialog
{
    Q_OBJECT
public:
    enum OrderMode {AddOrder, ViewOrder, EditOrder};

    explicit OrderWidget(OrderMode mode, QDialog *parent = 0);
    ~OrderWidget();

private slots:
    void on_cbCustomerType_activated(int index);

    void on_pbAction_clicked();

private:
    Ui::OrderWidget *ui;
    OrderMode mode_;
};

#endif // ORDERWIDGET_H
