#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "orderwidget.h"

#include <QMessageBox>
#include <QDebug>
#include <QIcon>
#include <QKeySequence>

#include "sqldatabasehelper.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();
    createToolBar();

    orderInfoWidget_ = new OrderInfoWidget(this);
    customerInfoWidget_ = new CustomerInfoWidget(this);

    ui->tabWidget->addTab(orderInfoWidget_, tr("Заказы"));
    ui->tabWidget->addTab(customerInfoWidget_, tr("Заказчики"));

    ui->tabWidget->setCurrentIndex(0);
//    ui->rbNaturalPerson->click();

    SqlDatabaseHelper sqlDatabaseHelper;

    QString databaseName = "Driver={SQL Server}; Database=mebel;";
    sqlDatabaseHelper.open("QODBC3", "127.0.0.1", databaseName, "mysql", "mysql");

    QStringList values = sqlDatabaseHelper.select("mebel.tb_order");
    Q_FOREACH(QString value, values) {
//        qDebug() << value;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int ret = QMessageBox::information(
        this, tr("Закрыть программу?"),
        tr("ВегаМебель"),
        QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::No) {
        event->ignore();
    }
}

void MainWindow::onAboutAct()
{

}

void MainWindow::onAddOrderAct()
{
    OrderWidget orderWidget(OrderWidget::AddOrder);
    orderWidget.exec();
//    emit orderInfoWidget_->updateTableWidgetItemData();
}

void MainWindow::onViewOrderAct()
{
    OrderWidget orderWidget(OrderWidget::ViewOrder);
    orderWidget.exec();
}

void MainWindow::onEditOrderAct()
{
    OrderWidget orderWidget(OrderWidget::EditOrder);
    orderWidget.exec();
}

void MainWindow::onDeleteOrderAct()
{
    int ret = QMessageBox::warning(
        this,
        tr("Точно удалить заказ?"),
        tr("mebel"),
        QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        qDebug() << tr("Заказ удален");
    }
}

void MainWindow::onShowReferenceAct()
{

}

void MainWindow::onPrintAct()
{

}

void MainWindow::createMenus()
{
    ui->menuProgram->addAction(actAbout_);
    ui->menuProgram->addSeparator();
    ui->menuProgram->addAction(actExit_);

    ui->menuOrder->addAction(actAddOrder_);
    ui->menuOrder->addAction(actViewOrder_);
    ui->menuOrder->addAction(actEditOrder_);
    ui->menuOrder->addAction(actDeleteOrder_);
    ui->menuOrder->addSeparator();
    ui->menuOrder->addAction(actPrint_);

    ui->menuHelp->addAction(actShowReference_);
}

void MainWindow::createActions()
{
    actAbout_ = new QAction(QIcon(""), tr("&О программе"), this);
//    actAbout_->setShortcut(QKeySequence:: ?);
    actAbout_->setStatusTip(tr("О программе"));
    connect(actAbout_, SIGNAL(triggered()), this, SLOT(onAboutAct()));

    actExit_ = new QAction(QIcon(""), tr("&Выход"), this);
//    actExit_->setShortcut(QKeySequence:: ?);
    actExit_->setStatusTip(tr("Выход"));
    connect(actExit_, SIGNAL(triggered()), this, SLOT(close()));

    actAddOrder_ = new QAction(QIcon(""), tr("&Добавить"), this);
    actAddOrder_->setShortcut(QKeySequence::New);
    actAddOrder_->setStatusTip(tr("Добавить новый заказ"));
    connect(actAddOrder_, SIGNAL(triggered()), this, SLOT(onAddOrderAct()));

    actViewOrder_ = new QAction(QIcon(""), tr("&Просмотреть"), this);
//    actViewOrder_->setShortcut(QKeySequence:: ?);
    actViewOrder_->setStatusTip(tr("Просмотреть заказ"));
    connect(actViewOrder_, SIGNAL(triggered()), this, SLOT(onViewOrderAct()));

    actEditOrder_ = new QAction(QIcon(""), tr("&Редактировать"), this);
//    actEditOrder_->setShortcut(QKeySequence:: ?);
    actEditOrder_->setStatusTip(tr("Редактировать заказ"));
    connect(actEditOrder_, SIGNAL(triggered()), this, SLOT(onEditOrderAct()));

    actDeleteOrder_ = new QAction(QIcon(""), tr("&Удалить"), this);
    actDeleteOrder_->setShortcut(QKeySequence::Delete);
    actDeleteOrder_->setStatusTip(tr("Удалить заказ"));
    connect(actDeleteOrder_, SIGNAL(triggered()), this, SLOT(onDeleteOrderAct()));

    actShowReference_ = new QAction(QIcon(""), tr("&Показать справку"), this);
//    actShowReference_->setShortcut(QKeySequence:: ?);
    actShowReference_->setStatusTip(tr("Показать справку"));
    connect(actShowReference_, SIGNAL(triggered()), this, SLOT(onShowReferenceAct()));

    actPrint_ = new QAction(QIcon(""), tr("&Печать"), this);
    actPrint_->setShortcut(QKeySequence::Print);
    actPrint_->setStatusTip(tr("Печать"));
    connect(actPrint_, SIGNAL(triggered()), this, SLOT(onPrintAct()));

    actViewOrder_->setEnabled(false);
    actEditOrder_->setEnabled(false);
    actDeleteOrder_->setEnabled(false);
    actPrint_->setEnabled(false);
}

void MainWindow::createToolBar()
{
    ui->mainToolBar->addAction(actAddOrder_);
    ui->mainToolBar->addAction(actViewOrder_);
    ui->mainToolBar->addAction(actEditOrder_);
    ui->mainToolBar->addAction(actDeleteOrder_);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(actPrint_);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(actExit_);
}

void MainWindow::on_rbNaturalPerson_clicked()
{
//    ui->swCustomers->setCurrentIndex(0);
}

void MainWindow::on_rbJuridicalPerson_clicked()
{
//    ui->swCustomers->setCurrentIndex(1);
}
