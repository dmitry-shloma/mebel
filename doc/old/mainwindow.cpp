#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlDatabase>
#include <QDir>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3", "mydbf");
    QString dbName = qApp->applicationDirPath () + QDir::separator () + "./../AstBase.DBF";
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug () << db.lastError().text();
        qDebug () << db.drivers ();
    }

#ifdef QT_DEBUG
    qDebug () << "db is open: " << db.isOpen ();
#endif

    QSqlQuery query;
    if (!query.exec ("SELECT * FROM \"AstBase.DBF\"")) {
        qDebug () << query.lastError ().text ();
    }

       QSqlTableModel *model = new QSqlTableModel(this->parentWidget (), db);
       model->setTable("");

         QTableView *view = new QTableView;
         view->setModel(model);
         view->show();


    db.close ();
    db = QSqlDatabase ();
    db.removeDatabase ("mydbf");
}

MainWindow::~MainWindow()
{
    delete ui;
}
