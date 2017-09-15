#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "addcontractwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    addContractAct_ = new QAction("add contract", this);
    connect(addContractAct_, SIGNAL(triggered()), this, SLOT(onAddContractAct()));

    printAct_ = new QAction("print", this);
    connect(addContractAct_, SIGNAL(triggered()), this, SLOT(onPrintAct()));

    ui->mainToolBar->addAction(addContractAct_);
    ui->mainToolBar->addAction(printAct_);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddContractAct()
{
    AddContractWidget addContractWidget;
    addContractWidget.exec();
}

void MainWindow::onPrintAct()
{

}
