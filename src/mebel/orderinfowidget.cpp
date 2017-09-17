#include "orderinfowidget.h"
#include "ui_orderinfowidget.h"

#include <QStringList>
#include <QTableWidgetItem>

OrderInfoWidget::OrderInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderInfoWidget)
{
    ui->setupUi(this);

    QStringList labels;
    labels << tr("№ договора") << tr("Дата договора") << tr("Вид заказчика")
           << tr("Заказчик") << tr("Тип мебели") << tr("Дата монтажа")
           << tr("Адрес монтажа") << tr("Цена") << tr("Первый взнос")
           << tr("Остаток") << tr("Состояние заказа") << tr("Примечание");
    ui->twOrders->setColumnCount(labels.size());
    ui->twOrders->setHorizontalHeaderLabels(labels);

    connect(
        this,
        SIGNAL(updateTableWidgetItemData(const QStringList &data)),
        this,
        SLOT(onUpdateTableWidgetItemData(QStringList)));
}

OrderInfoWidget::~OrderInfoWidget()
{
    delete ui;
}

void OrderInfoWidget::onUpdateTableWidgetItemData(const QStringList &data)
{
    ui->twOrders->clearContents();

    if (data.isEmpty()) {
        return;
    }

    int row = ui->twOrders->rowCount();
    ui->twOrders->insertRow(row);

    int col = 0;
    Q_FOREACH(QString text, data) {
        ui->twOrders->setItem(row, col++, new QTableWidgetItem(text));
    }
}
