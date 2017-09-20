#include "sqldatabasehelper.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>

SqlDatabaseHelper::SqlDatabaseHelper()
    : isOpen_(false)
{
}

void SqlDatabaseHelper::open(const QString &type,
                             const QString &hostName,
                             const QString &databaseName,
                             const QString &userName, const QString &password)
{
    db_ = QSqlDatabase::addDatabase(type);
    db_.setHostName(hostName);
    db_.setDatabaseName(databaseName);
    isOpen_ = db_.open(userName, password);
    if (!isOpen_) {
        qDebug() << "text" << db_.lastError().text();
        qDebug() << "databaseText" << db_.lastError().databaseText();
        qDebug() << "driverText" << db_.lastError().driverText();
    }
}

void SqlDatabaseHelper::close()
{
    if (!isOpen_) {
        // throw
        return;
    }
    QSqlDatabase::removeDatabase(db_.connectionName());
}

QStringList SqlDatabaseHelper::select(const QString &tableName,
                                      const QString &filter)
{
    if (!isOpen_) {
//        throw
        return QStringList();
    }

    QStringList values;

    QSqlQuery query(QString("SELECT * FROM %0;").arg(tableName), db_);
    int columnCount = query.record().count();

    while (query.next()) {
        for (int i = 0; i < columnCount; ++i) {
            values << query.value(i).toString();
        }
    }
    return values;
}

quint32 SqlDatabaseHelper::insert(const QString &tableName,
                               const QStringList &columns,
                               const QStringList &values)
{
    if (!isOpen_) {
//        throw
        return 0;
    }

    QString columnsWithCommas = columns.join(",");
    QString valuesWithCommas = values.join(",");
    QSqlQuery query(QString("INSERT INTO %0 (%1) VALUES (%2);").arg(tableName)
                    .arg(columnsWithCommas).arg(valuesWithCommas), db_);
    if (query.lastError().type() != QSqlError::NoError) {
        qDebug() << "text" << query.lastError().text();
        qDebug() << "databaseText" << query.lastError().databaseText();
        qDebug() << "driverText" << query.lastError().driverText();
        return 0;
    }

    return query.lastInsertId().toInt();
}
