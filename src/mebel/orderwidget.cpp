#include "orderwidget.h"
#include "ui_orderwidget.h"

#include <QDebug>
#include <QTreeWidgetItem>
#include <QCheckBox>

OrderWidget::OrderWidget(OrderMode mode, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::OrderWidget),
    mode_(mode)
{
    ui->setupUi(this);
    switch (mode_) {
    case AddOrder:
        ui->lbTitle->setText(ui->lbTitle->text().arg(tr("Добавление")));
        ui->pbAction->setText(tr("Добавить"));
        break;
    case ViewOrder:
        ui->lbTitle->setText(ui->lbTitle->text().arg(tr("Просмотр")));
        ui->pbAction->setText(tr("Закрыть"));
        break;
    case EditOrder:
        ui->lbTitle->setText(ui->lbTitle->text().arg(tr("Редактирование")));
        ui->pbAction->setText(tr("Сохранить"));
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

void OrderWidget::on_pbAction_clicked()
{
    switch (mode_) {
    case AddOrder:
        // TODO: add action
        break;
    case ViewOrder:
        close();
        break;
    case EditOrder:
        // TODO: edit action
        break;
    }
}
