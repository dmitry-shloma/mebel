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
    enum CustomerSpecies {NaturalPerson = 1, JuridicalPerson = 2};

    explicit OrderWidget(OrderMode mode, QDialog *parent = 0);
    ~OrderWidget();

private slots:
    void on_cbCustomerSpecies_currentIndexChanged(int index);
    void on_cbFurnitureSpecies_currentIndexChanged(int index);
    void on_cbOrderSpecies_activated(int index);

    void onAddOrderActionSelected();
    void onViewOrderActionSelected();
    void onEditOrderActionSelected();

    void on_chbIisExw_clicked();

private:
    void addOrderInit();
    void viewOrderInit();
    void editOrderInit();

    Ui::OrderWidget *ui;
    OrderMode mode_;
};

#endif // ORDERWIDGET_H
