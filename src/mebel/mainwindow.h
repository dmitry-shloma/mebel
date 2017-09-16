#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onAddOrderAct();
    void onPrintAct();

private:
    Ui::MainWindow *ui;
    QAction *addOrderAct_;
    QAction *printAct_;
};

#endif // MAINWINDOW_H
