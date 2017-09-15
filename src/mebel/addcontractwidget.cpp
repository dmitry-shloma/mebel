#include "addcontractwidget.h"
#include "ui_addcontractwidget.h"

#include <QDebug>
#include <QTreeWidgetItem>
#include <QCheckBox>

AddContractWidget::AddContractWidget(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::AddContractWidget)
{
    ui->setupUi(this);
    ui->sw->setCurrentIndex(0);

    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);
        treeItem->setFlags(treeItem->flags() | Qt::ItemIsUserCheckable);
        treeItem->setCheckState(0, Qt::Unchecked);
        treeItem->setCheckState(1, Qt::Unchecked);
        treeItem->setCheckState(2, Qt::Unchecked);
}

AddContractWidget::~AddContractWidget()
{
    delete ui;
}

void AddContractWidget::on_cbCustomerType_activated(int index)
{
    ui->sw->setCurrentIndex(index);
}
