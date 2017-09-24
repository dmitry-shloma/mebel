#ifndef ORDERINFOWIDGET_H
#define ORDERINFOWIDGET_H

#include <QWidget>
#include <QStringList>

namespace Ui {
class OrderInfoWidget;
}

class OrderInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OrderInfoWidget(QWidget *parent = 0);
    ~OrderInfoWidget();

    void onUpdateTableWidgetItemData();

private:
    Ui::OrderInfoWidget *ui;
};

#endif // ORDERINFOWIDGET_H
