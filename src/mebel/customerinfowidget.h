#ifndef CUSTOMERINFOWIDGET_H
#define CUSTOMERINFOWIDGET_H

#include <QWidget>

namespace Ui {
class CustomerInfoWidget;
}

class CustomerInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomerInfoWidget(QWidget *parent = 0);
    ~CustomerInfoWidget();

private:
    Ui::CustomerInfoWidget *ui;
};

#endif // CUSTOMERINFOWIDGET_H
