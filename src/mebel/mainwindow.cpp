#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "orderwidget.h"

#include <QMessageBox>
#include <QDebug>
#include <QIcon>
#include <QKeySequence>

#include "sqldatabasehelper.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(Settings::getInstance().getProjectName());

    createActions();
    createMenus();
    createToolBar();

    orderInfoWidget_ = new OrderInfoWidget(this);
    customerInfoWidget_ = new CustomerInfoWidget(this);

    ui->tabWidget->addTab(orderInfoWidget_, "Заказы");
    ui->tabWidget->addTab(customerInfoWidget_, "Заказчики");

    ui->tabWidget->setCurrentIndex(0);
//    ui->rbNaturalPerson->click();

    orderInfoWidget_->onUpdateTableWidgetItemData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int ret = QMessageBox::information(
                this,
                Settings::getInstance().getProjectName(),
                "Закрыть программу?",
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
    orderInfoWidget_->onUpdateTableWidgetItemData();
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
        "Точно удалить заказ?",
        Settings::getInstance().getProjectName(),
        QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        qDebug() << "Заказ удален";
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
    actAbout_ = new QAction(QIcon(""), "&О программе", this);
//    actAbout_->setShortcut(QKeySequence:: ?);
    actAbout_->setStatusTip("О программе");
    connect(actAbout_, SIGNAL(triggered()), this, SLOT(onAboutAct()));

    actExit_ = new QAction(QIcon(""), "&Выход", this);
//    actExit_->setShortcut(QKeySequence:: ?);
    actExit_->setStatusTip("Выход");
    connect(actExit_, SIGNAL(triggered()), this, SLOT(close()));

    actAddOrder_ = new QAction(QIcon(""), "&Добавить", this);
    actAddOrder_->setShortcut(QKeySequence::New);
    actAddOrder_->setStatusTip("Добавить новый заказ");
    connect(actAddOrder_, SIGNAL(triggered()), this, SLOT(onAddOrderAct()));

    actViewOrder_ = new QAction(QIcon(""), "&Просмотреть", this);
//    actViewOrder_->setShortcut(QKeySequence:: ?);
    actViewOrder_->setStatusTip("Просмотреть заказ");
    connect(actViewOrder_, SIGNAL(triggered()), this, SLOT(onViewOrderAct()));

    actEditOrder_ = new QAction(QIcon(""), "&Редактировать", this);
//    actEditOrder_->setShortcut(QKeySequence:: ?);
    actEditOrder_->setStatusTip("Редактировать заказ");
    connect(actEditOrder_, SIGNAL(triggered()), this, SLOT(onEditOrderAct()));

    actDeleteOrder_ = new QAction(QIcon(""), "&Удалить", this);
    actDeleteOrder_->setShortcut(QKeySequence::Delete);
    actDeleteOrder_->setStatusTip("Удалить заказ");
    connect(actDeleteOrder_, SIGNAL(triggered()), this, SLOT(onDeleteOrderAct()));

    actShowReference_ = new QAction(QIcon(""), "&Показать справку", this);
//    actShowReference_->setShortcut(QKeySequence:: ?);
    actShowReference_->setStatusTip("Показать справку");
    connect(actShowReference_, SIGNAL(triggered()), this, SLOT(onShowReferenceAct()));

    actPrint_ = new QAction(QIcon(""), "&Печать", this);
    actPrint_->setShortcut(QKeySequence::Print);
    actPrint_->setStatusTip("Печать");
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
