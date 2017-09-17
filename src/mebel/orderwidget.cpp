#include "orderwidget.h"
#include "ui_orderwidget.h"

#include <QDebug>
#include <QTreeWidgetItem>
#include <QCheckBox>

OrderWidget::OrderWidget(OrderMode mode, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::OrderWidget)
{
    ui->setupUi(this);
    switch (mode) {
    case AddOrder:
        ui->lbTitle->setText(ui->lbTitle->text().arg(tr("Добавление")));
        break;
    case ViewOrder:
        ui->lbTitle->setText(ui->lbTitle->text().arg(tr("Просмотр")));
        break;
    case EditOrder:
        ui->lbTitle->setText(ui->lbTitle->text().arg(tr("Редактирование")));
        break;
    }

    ui->sw->setCurrentIndex(0);

    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);
        treeItem->setFlags(treeItem->flags() | Qt::ItemIsUserCheckable);
        treeItem->setCheckState(0, Qt::Unchecked);
        treeItem->setCheckState(1, Qt::Unchecked);
        treeItem->setCheckState(2, Qt::Unchecked);
}

OrderWidget::~OrderWidget()
{
    delete ui;
}

void OrderWidget::on_cbCustomerType_activated(int index)
{
    ui->sw->setCurrentIndex(index);
}
