#include "orderwidget.h"
#include "ui_orderwidget.h"

#include <QDebug>
#include <QTreeWidgetItem>
#include <QCheckBox>
#include <QDate>
#include <QMessageBox>
#include <QList>
#include <QStringList>

#include "sqldatabasehelper.h"
#include "settings.h"

OrderWidget::OrderWidget(OrderMode mode, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::OrderWidget),
    mode_(mode)
{
    ui->setupUi(this);

    setWindowTitle(Settings::getInstance().getProjectName());

    switch (mode_) {
    case AddOrder:
        addOrderInit();
        connect(ui->pbAction,
                SIGNAL(clicked()),
                this,
                SLOT(onAddOrderActionSelected()));
        break;
    case ViewOrder:
        viewOrderInit();
        connect(ui->pbAction,
                SIGNAL(clicked()),
                this,
                SLOT(onViewOrderActionSelected()));
        break;
    case EditOrder:
        editOrderInit();
        connect(ui->pbAction,
                SIGNAL(clicked()),
                this,
                SLOT(onEditOrderActionSelected()));
        break;
    }

    ui->swPerson->setCurrentIndex(0);
}

OrderWidget::~OrderWidget()
{
    delete ui;
}

void OrderWidget::on_cbCustomerSpecies_currentIndexChanged(int index)
{
    ui->swPerson->setCurrentIndex(index);
}

void OrderWidget::on_cbFurnitureSpecies_currentIndexChanged(int index)
{
    // считывание типа мебели из БД, в зависимости от выбранного
    // в cbFurnitureSpecies
    QString filter = QString("WHERE furniture_species_id = %0")
            .arg(ui->cbFurnitureSpecies->itemData(index).toInt());
    QList<QStringList> tableValues = SqlDatabaseHelper::getInstance().select(
                "tb_furniture_type", QStringList("*"), filter);
    ui->twFurnitureType->clear();
    int column = 0;
    Q_FOREACH(QStringList row, tableValues) {
        QVariant id = row.at(0);
        QString type = row.at(1);

        // TODO: реализовать равномерное заполнение
        ui->twFurnitureType->header()->setMinimumSectionSize(150);
        QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->twFurnitureType);
        treeItem->setText(column, type);
        treeItem->setData(column, Qt::UserRole, id);
        treeItem->setFlags(treeItem->flags() | Qt::ItemIsUserCheckable);
        treeItem->setCheckState(column, Qt::Unchecked);
//        column++;
    }
}

void OrderWidget::onAddOrderActionSelected()
{
    const int col = 0;
    int topLevelItemCount = ui->twFurnitureType->topLevelItemCount();
    for (int i = 0; i < topLevelItemCount; ++i) {
        QTreeWidgetItem *item = ui->twFurnitureType->topLevelItem(i);
        if (item->checkState(col) == Qt::Checked) {
            qDebug() << item->text(col) << item->data(col, Qt::UserRole).toInt();
        }
    }
    return;

    // запись данных заказа в БД
    int customerSpecies = ui->cbCustomerSpecies->
            itemData(ui->cbCustomerSpecies->currentIndex()).toInt();

    /* Запись в таблицу tb_customer [заказчик] */
    QStringList columns;
    columns << "fullname_or_name" << "registration_or_juridical_address"
            << "phone" << "email" << "information_source_id" << "note";

    QStringList values;
    if (customerSpecies == NaturalPerson) {
        values << ui->leFullname->text() << ui->ptRegistrationAddress->toPlainText();
    } else if (customerSpecies == JuridicalPerson) {
        values << ui->leName->text() << ui->ptJuridicalAddress->toPlainText();
    }

    values << ui->lePhone->text() << ui->leEmail->text()
           << ui->cbInformationSource->itemData(ui->cbInformationSource->currentIndex()).toString()
           << ui->ptCustomerNote->toPlainText();

    QStringList::iterator i;
    for (i = values.begin(); i != values.end(); ++i) { // decorate with '
        *i = QString("'%0'").arg(*i);
    }
    int customer_id = SqlDatabaseHelper::getInstance().insert("tb_customer", columns, values);

    /* Запись в таблицу tb_natural_person или tb_juridical_person в зависимости от типа заказчика */
    switch (customerSpecies) {  // проверка выбранного вида заказчика
    case NaturalPerson:
        /* Запись в таблицу tb_natural_person [физическое лицо] */
        columns.clear();
        columns << "id" << "birth_date" << "ppt_series_and_number"
                << "ppt_issued_by" << "ppt_issue_date";

        values.clear();
        values << QString::number(customer_id) << ui->deBirthDate->date().toString("yyyy-MM-dd")
               << ui->lePptSeriesAndNumber->text() << ui->dePptIssueDate->date().toString("yyyy-MM-dd")
               << ui->dePptIssueDate->date().toString("yyyy-MM-dd");
        for (i = values.begin(); i != values.end(); ++i) { // decorate with '
            *i = QString("'%0'").arg(*i);
        }
        SqlDatabaseHelper::getInstance().insert("tb_natural_person", columns, values);
        break;

    case JuridicalPerson:
        /* Запись в таблицу tb_juridical_person [юридическое лицо] */
        columns.clear();
        columns << "id" << "juridical_name" << "inn" << "ogrn"
                << "checking_account" << "bank_name" << "corr_account" << "bik"
                << "contact_person";

        values.clear();
        values << QString::number(customer_id) << ui->ptJuridicalName->toPlainText()
               << ui->leInn->text() << ui->leOgrn->text()
               << ui->leCheckingAccount->text() << ui->ptBankName->toPlainText()
               << ui->leCorrAccount->text() << ui->leBik->text()
               << ui->leContactPerson->text();
        for (i = values.begin(); i != values.end(); ++i) { // decorate with '
            *i = QString("'%0'").arg(*i);
        }
        SqlDatabaseHelper::getInstance().insert("tb_juridical_person", columns, values);
        break;
    }

    /* Запись в таблицу tb_order [заказ] */
    columns.clear();
    columns << "contract_number" << "contract_date" << "customer_species_id"
            << "customer_id" << "order_species_id" << "furniture_type_id"
            << "installation_date" << "is_exw" << "installation_address"
            << "price" << "initial_payment" << "balance" << "order_state_id"
            << "order_state_change_history" << "note";

    values.clear();
    int order_species_id = ui->cbOrderSpecies->itemData(ui->cbOrderSpecies->currentIndex()).toInt();
    int furniture_type_id = 1;/*ui->twFurnitureType->ite*/
    int order_state_id = ui->cbOrderState->itemData(ui->cbOrderState->currentIndex()).toInt();
    bool iisExw = ui->chbIisExw->isChecked();
    QString installationAddress = iisExw ? "NULL" : ui->ptInstallationAddress->toPlainText();
    values << ui->leContractNumber->text() << ui->deContractDate->date().toString("yyyy-MM-dd")
           << QString::number(customerSpecies) << QString::number(customer_id)
           << QString::number(order_species_id) << QString::number(furniture_type_id)
           << ui->deInstallationDate->date().toString("yyyy-MM-dd")
           << QString::number(iisExw)
           << installationAddress
           << ui->dsbPrice->text().replace(",", ".") << ui->dsbInitialPayment->text().replace(",", ".")
           << ui->dsbBalance->text().replace(",", ".") << QString::number(order_state_id)
           << QString("NULL") << ui->ptOrderNote->toPlainText();
    for (i = values.begin(); i != values.end(); ++i) { // decorate with '
        *i = QString("'%0'").arg(*i);
    }
    SqlDatabaseHelper::getInstance().insert("tb_order", columns, values);

    QMessageBox::information(
                this,
                Settings::getInstance().getProjectName(),
                "Заказ успешно добавлен");
    close();
}

void OrderWidget::onViewOrderActionSelected()
{
    close();
}

void OrderWidget::onEditOrderActionSelected()
{
    QMessageBox::information(
                this,
                Settings::getInstance().getProjectName(),
                "Изменения по заказу успешно сохранены");
    close();
}

void OrderWidget::addOrderInit()
{
    ui->lbTitle->setText(ui->lbTitle->text().arg("Добавление"));
    ui->pbAction->setText("Добавить");

    ui->deContractDate->setDate(QDate::currentDate());
    // 30 рабочих дней или 38 календарных
    // TODO: Подсвечивать текущую дату, а может еще подсвечивать
    // от текущей даты до даты монтажа
    ui->deInstallationDate->setDate(QDate::currentDate().addDays(38));

    // TODO: чтение номера предыдущего договора и увеличение его на один

    // считывание типа заказчика из БД
    QList<QStringList> tableValues = SqlDatabaseHelper::getInstance().select(
                "tb_customer_species");
    ui->cbCustomerSpecies->clear();
    Q_FOREACH(QStringList row, tableValues) {
        QVariant id = row.at(0);
        QString species = row.at(1);
        ui->cbCustomerSpecies->addItem(species, id);
    }

    // считывание вида мебели из БД
    tableValues = SqlDatabaseHelper::getInstance().select(
                "tb_furniture_species");
    ui->cbFurnitureSpecies->clear();
    Q_FOREACH(QStringList row, tableValues) {
        QVariant id = row.at(0);
        QString species = row.at(1);
        ui->cbFurnitureSpecies->addItem(species, id);
    }

    // считывание вида заказа из БД
    tableValues = SqlDatabaseHelper::getInstance().select(
                "tb_order_species");
    ui->cbOrderSpecies->clear();
    Q_FOREACH(QStringList row, tableValues) {
        QVariant id = row.at(0);
        QString species = row.at(1);
        ui->cbOrderSpecies->addItem(species, id);
    }

    // считывание откуда о нас узнали из БД
    tableValues = SqlDatabaseHelper::getInstance().select(
                "tb_information_source");
    ui->cbInformationSource->clear();
    Q_FOREACH(QStringList row, tableValues) {
        QVariant id = row.at(0);
        QString source = row.at(1);
        ui->cbInformationSource->addItem(source, id);
    }

    // считывание статуса заказа из БД
    tableValues = SqlDatabaseHelper::getInstance().select(
                "tb_order_state");
    ui->cbOrderState->clear();
    Q_FOREACH(QStringList row, tableValues) {
        QVariant id = row.at(0);
        QString state = row.at(1);
        ui->cbOrderState->addItem(state, id);
    }
}

void OrderWidget::viewOrderInit()
{
    ui->lbTitle->setText(ui->lbTitle->text().arg("Просмотр"));
    ui->pbAction->setText("Закрыть");
}

void OrderWidget::editOrderInit()
{
    ui->lbTitle->setText(ui->lbTitle->text().arg("Редактирование"));
    ui->pbAction->setText("Сохранить");
}

void OrderWidget::on_cbOrderSpecies_activated(int index)
{
    Q_UNUSED(index);
    QMessageBox::warning(
                this,
                Settings::getInstance().getProjectName(),
                "Не реализовано");
    ui->cbOrderSpecies->setCurrentIndex(0);
}

void OrderWidget::on_chbIisExw_clicked()
{
    ui->ptInstallationAddress->clear();
    ui->ptInstallationAddress->setEnabled(!ui->chbIisExw->isChecked());
}
