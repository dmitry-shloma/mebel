#include "sqldatabasehelper.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

SqlDatabaseHelper::SqlDatabaseHelper()
    : isOpen_(false)
{
}

void SqlDatabaseHelper::open(const QString &type, const QString &hostName,
                             const QString &databaseName,
                             const QString &userName, const QString &password)
{
    db_ = QSqlDatabase::addDatabase(type);
    db_.setHostName(hostName);
    db_.setDatabaseName(databaseName);
    isOpen_ = db_.open(userName, password);
    qDebug() << db_.lastError().text();
    qDebug() << db_.lastError().databaseText();
    qDebug() << db_.lastError().driverText();
}

void SqlDatabaseHelper::close()
{
    QSqlDatabase::removeDatabase(db_.connectionName());
}

QStringList SqlDatabaseHelper::select(const QString &tableName,
                                      const QString &filter)
{
    qDebug() << isOpen_;
    if (!isOpen_) {
//        throw
        return QStringList();
    }


    QStringList values;
    QSqlQuery query(QString("SELECT * FROM %0").arg(tableName), db_);
    while (query.next()) {
        qDebug() << query.value(0);
    }
    return values;
}

void SqlDatabaseHelper::insert(const QString &tableName,
                               const QStringList &columns,
                               const QStringList &values)
{
    if (!isOpen_) {
//        throw
        return;
    }

    QString columnsStr = columns.join(", ");
    QString valuesStr = values.join(", ");
    QString queryStr = QString("INSERT INTO %1 (%2) VALUES (%3) RETURNING id").arg(tableName)
            .arg(columnsStr)
            .arg(valuesStr);
    qDebug("%s", queryStr.toStdString().c_str());
    QSqlQuery query(queryStr, db_);
    while (query.next()) {
//        id = query.value(0).toInt();
    }
}
