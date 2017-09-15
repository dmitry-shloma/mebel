#include "addcontractwidget.h"
#include "ui_addcontractwidget.h"

#include <QDebug>

AddContractWidget::AddContractWidget(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::AddContractWidget)
{
    ui->setupUi(this);
}

AddContractWidget::~AddContractWidget()
{
    delete ui;
}

void AddContractWidget::on_cbCustomerType_currentIndexChanged(int index)
{
    ui->swCustomerType->setCurrentIndex(index);
}
