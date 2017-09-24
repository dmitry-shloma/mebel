#include "orderinfowidget.h"
#include "ui_orderinfowidget.h"

#include <QStringList>
#include <QTableWidgetItem>

#include "settings.h"
#include "sqldatabasehelper.h"

OrderInfoWidget::OrderInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderInfoWidget)
{
    ui->setupUi(this);

    QStringList labels;
    labels << "№ договора" << "Дата договора" << "Вид заказчика"
           << "Заказчик" << "Тип мебели" << "Дата монтажа"
           << "Адрес монтажа" << "Цена" << "Первый взнос"
           << "Остаток" << "Состояние заказа" << "Примечание";
    ui->twOrders->setColumnCount(labels.size());
    ui->twOrders->setHorizontalHeaderLabels(labels);
}

OrderInfoWidget::~OrderInfoWidget()
{
    delete ui;
}

void OrderInfoWidget::onUpdateTableWidgetItemData()
{
//    ui->twOrders->clearContents();
    ui->twOrders->setRowCount(0);

    // считывание инфорамции о заказе из БД
    QStringList columnList;
    columnList << "contract_number" << "contract_date" << "customer_species_id"
               << "customer_id" << "furniture_type_id" << "installation_date"
               << "installation_address" << "price" << "initial_payment"
               << "balance" << "order_state_id" << "note";
    QList<QStringList> tableValues = SqlDatabaseHelper::getInstance().select("tb_order", columnList);

    if (tableValues.isEmpty()) {
        return;
    }

    Q_FOREACH(QStringList rowValues, tableValues) {
        int row = ui->twOrders->rowCount();
        ui->twOrders->insertRow(row);

        int col = 0;
        Q_FOREACH(QString text, rowValues) {
            ui->twOrders->setItem(row, col++, new QTableWidgetItem(text));
        }
    }
}
