#include "addorderwidget.h"
#include "ui_addorderwidget.h"

#include <QDebug>
#include <QTreeWidgetItem>
#include <QCheckBox>

AddOrderWidget::AddOrderWidget(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::AddOrderWidget)
{
    ui->setupUi(this);
    ui->sw->setCurrentIndex(0);

    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);
        treeItem->setFlags(treeItem->flags() | Qt::ItemIsUserCheckable);
        treeItem->setCheckState(0, Qt::Unchecked);
        treeItem->setCheckState(1, Qt::Unchecked);
        treeItem->setCheckState(2, Qt::Unchecked);
}

AddOrderWidget::~AddOrderWidget()
{
    delete ui;
}

void AddOrderWidget::on_cbCustomerType_activated(int index)
{
    ui->sw->setCurrentIndex(index);
}
