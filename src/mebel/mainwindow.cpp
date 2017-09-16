#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "addorderwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    addOrderAct_ = new QAction("add order", this);
    connect(addOrderAct_, SIGNAL(triggered()), this, SLOT(onAddOrderAct()));

    printAct_ = new QAction("print", this);
    connect(addOrderAct_, SIGNAL(triggered()), this, SLOT(onPrintAct()));

    ui->mainToolBar->addAction(addOrderAct_);
    ui->mainToolBar->addAction(printAct_);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddOrderAct()
{
    AddOrderWidget addOrderWidget;
    addOrderWidget.exec();
}

void MainWindow::onPrintAct()
{

}
