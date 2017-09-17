#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QCloseEvent>

#include "orderinfowidget.h"
#include "customerinfowidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void onAboutAct();
    void onAddOrderAct();
    void onViewOrderAct();
    void onEditOrderAct();
    void onDeleteOrderAct();
    void onShowReferenceAct();
    void onPrintAct();

    void on_rbNaturalPerson_clicked();
    void on_rbJuridicalPerson_clicked();

private:
    void createActions();
    void createMenus();
    void createToolBar();

    Ui::MainWindow *ui;

    QAction *actAbout_;
    QAction *actExit_;
    QAction *actAddOrder_;
    QAction *actViewOrder_;
    QAction *actEditOrder_;
    QAction *actDeleteOrder_;
    QAction *actShowReference_;
    QAction *actPrint_;

    OrderInfoWidget *orderInfoWidget_;
    CustomerInfoWidget *customerInfoWidget_;
};

#endif // MAINWINDOW_H
