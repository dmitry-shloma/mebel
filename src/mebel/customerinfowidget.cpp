#include "customerinfowidget.h"
#include "ui_customerinfowidget.h"

CustomerInfoWidget::CustomerInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerInfoWidget)
{
    ui->setupUi(this);
}

CustomerInfoWidget::~CustomerInfoWidget()
{
    delete ui;
}
